#!/bin/bash
modules=(cod_support)
themes=()

pull_git() {
    cd $BUILD_PATH/cod_profile
    if [[ -n $RESET ]]; then
      git reset --hard HEAD
    fi
    git pull origin 7.x-1.x

    cd $BUILD_PATH/repos/modules/contrib
    for i in "${modules[@]}"; do
      echo $i
      cd $i
      if [[ -n $RESET ]]; then
        git reset --hard HEAD
      fi
      git pull origin 7.x-1.x
      cd ..
    done
}

release_notes() {
  rm -rf rn.txt
  #pull_git $BUILD_PATH
  OUTPUT="<h2>Release Notes for $RELEASE</h2>"
  cd $BUILD_PATH/cod_profile
  OUTPUT="$OUTPUT <h3>cod Profile:</h3> `drush rn --date $FROM_DATE $TO_DATE`"

  cd $BUILD_PATH/repos/modules/contrib
  for i in "${modules[@]}"; do
    echo $i
    cd $i
    RN=`drush rn --date $FROM_DATE $TO_DATE`
    if [[ -n $RN ]]; then
      OUTPUT="$OUTPUT <h3>$i:</h3> $RN"
    fi
    cd ..
  done

  echo $OUTPUT >> $BUILD_PATH/rn.txt
}

build_distro() {
  if [[ -d $BUILD_PATH ]]; then
      cd $BUILD_PATH
      #backup the sites directory
      if [[ -d docroot ]]; then
        rm -rf ./docroot
      fi
      # do we have the profile?
      if [[ -d $BUILD_PATH/cod_profile ]]; then
        if [[ -d $BUILD_PATH/repos ]]; then
          rm -f /tmp/cod.tar.gz
          drush make --no-cache --prepare-install --drupal-org=core $BUILD_PATH/cod_profile/drupal-org-core.make $BUILD_PATH/docroot
          drush make --no-cache --no-core --contrib-destination --concurrency=5 --tar $BUILD_PATH/cod_profile/drupal-org.make /tmp/cod
        else
          mkdir -p $BUILD_PATH/repos/modules/contrib
          cd $BUILD_PATH/repos/modules/contrib
          for i in "${modules[@]}"; do
            echo "bringing in ${i} for $USERNAME";
            if [[ -n $USERNAME ]]; then
              git clone ${USERNAME}@git.drupal.org:project/${i}.git
            else
              git clone http://git.drupal.org/project/${i}.git
            fi
          done
          cd $BUILD_PATH/repos
          mkdir -p $BUILD_PATH/repos/themes/contrib
          cd $BUILD_PATH/repos/themes/contrib
          for i in "${themes[@]}"; do
            if [[ -n $USERNAME ]]; then
              git clone ${USERNAME}@git.drupal.org:project/${i}.git
            else
              git clone http://git.drupal.org/project/${i}.git
            fi
          done
          build_distro $BUILD_PATH
        fi
        # symlink the profile sites folder to our dev copy
        cd docroot
        if [[ -d $BUILD_PATH/sites ]]; then
          rm -rf $BUILD_PATH/docroot/sites
          ln -s ../sites $BUILD_PATH/docroot/sites
        else
          mv $BUILD_PATH/docroot/sites $BUILD_PATH/sites
          ln -s ../sites $BUILD_PATH/docroot/sites
        fi
        chmod -R 777 $BUILD_PATH/docroot/sites/default

        ## put cod profile and modules into the profile folder
        rm -rf docroot/profiles/cod
        if [ -a $BUILD_PATH/repos.txt ]; then
          UNTAR="tar -zxvf /tmp/cod.tar.gz -X $BUILD_PATH/repos.txt"
        else
          cd $BUILD_PATH/repos
          find * -mindepth 1 -maxdepth 2 -type d -not -path ".*" -not -path "modules/.*" -not -path "themes/.*" -not -path "modules/contrib" -not -path "themes/contrib" > $BUILD_PATH/repos.txt
          # exclude repos since we're updating already by linking it to the repos directory.
          UNTAR="tar -zxvf /tmp/cod.tar.gz -X $BUILD_PATH/repos.txt"
        fi
        cd $BUILD_PATH/docroot/profiles
        eval $UNTAR
        cd cod
        ln -s ../../../cod_profile/* .
        ln -s ../../../../cod_profile/modules/cod ${BUILD_PATH}/docroot/profiles/cod/modules/
        ln -s ../../../../cod_profile/themes/cod ${BUILD_PATH}/docroot/profiles/cod/themes/
        for line in $(cat $BUILD_PATH/repos.txt); do
          ln -s ../../../../../repos/${line} ${BUILD_PATH}/docroot/profiles/cod/$(echo ${line} | awk -F/ '{print $1}')/contrib/
        done
        chmod -R 775 $BUILD_PATH/docroot/profiles/cod
      else
        if [[ -n $USERNAME ]]; then
          git clone --branch 7.x-1.x ${USERNAME}@git.drupal.org:project/cod.git cod_profile
        else
          git clone http://git.drupal.org/project/cod.git cod_profile
        fi
        build_distro $BUILD_PATH
      fi
  else
    mkdir $BUILD_PATH
    build_distro $BUILD_PATH $USERNAME
  fi
}

# This allows you to test the make file without needing to upload it to drupal.org and run the main make file.
update() {
  if [[ -d $DOCROOT ]]; then
    cd $DOCROOT
    # do we have the profile?
    if [[ -d $DOCROOT/profiles/cod ]]; then
      # do we have an installed cod profile?
        sudo rm -f /tmp/docroot.tar.gz
        sudo rm -f /tmp/cod.tar.gz
        drush make --tar --drupal-org=core profiles/cod/drupal-org-core.make /tmp/docroot
        drush make --tar --drupal-org profiles/cod/drupal-org.make /tmp/cod
        cd ..
        tar -zxvf /tmp/docroot.tar.gz
        cd $DOCROOT/profiles/modules/contrib
        # remove the symlinks in the repos before we execute
        find . -mindepth 2 -type l | awk -F/ '{print $5}' | sed '/^$/d' > /tmp/repos.txt
        # exclude repos since we're updating already by linking it to the repos directory.
        UNTAR="tar -zxvf /tmp/cod.tar.gz -X /tmp/repos.txt"
        eval $UNTAR
        echo "Successfully Updated drupal from make files"
        exit 0
    fi
  fi
  echo "Unable to find Build path or drupal root. Please run build first"
  exit 1
}

abspath() {
  local thePath
  if [[ ! "$BUILD_PATH" =~ ^/ ]];then
    thePath="$PWD/$BUILD_PATH"
  else
    thePath="$BUILD_PATH"
  fi
  echo "$thePath"|(
    IFS=/
    read -a parr
    declare -a outp
    for i in "${parr[@]}";do
      case "$i" in
      ''|.) continue ;;
      ..)
        len=${#outp[@]}
        if ((len==0));then
          continue
        else
          unset outp[$((len-1))]
        fi
        ;;
      *)
        len=${#outp[@]}
        outp[$len]="$i"
        ;;
      esac
    done
    echo /"${outp[*]}"
  )
}

case $1 in
  pull)
    if [[ -n $2 ]]; then
      BUILD_PATH=$2
      if [[ -n $3 ]]; then
       RESET=1
      fi
    else
      echo "Usage: build_distro.sh pull [build_path]"
      exit 1
    fi
    BUILD_PATH=$(abspath)
    pull_git $BUILD_PATH $RESET;;
  build)
    if [[ -n $2 ]]; then
      BUILD_PATH=$2
    else
      echo "Usage: build_distro.sh build [build_path]"
      exit 1
    fi
    if [[ -n $3 ]]; then
      USERNAME=$3
    fi
    BUILD_PATH=$(abspath)
    build_distro $BUILD_PATH $USERNAME;;
  update)
    if [[ -n $2 ]]; then
      DOCROOT=$2
    else
      echo "Usage: build_distro.sh test_makefile [build_path]"
      exit 1
    fi
    if [[ -n $3 ]]; then
      USERNAME=$3
    fi
    BUILD_PATH=$(abspath)
    update $DOCROOT;;
  rn)
    if [[ -n $2 ]] && [[ -n $3 ]] && [[ -n $4 ]] && [[ -n $5 ]]; then
      BUILD_PATH=$2
      RELEASE=$3
      FROM_DATE=$4
      TO_DATE=$5
    else
      echo "Usage: build_distro.sh rn [build_path] [release] [from_date] [to_date]"
      exit 1
    fi
    BUILD_PATH=$(abspath)
    release_notes $BUILD_PATH $RELEASE $FROM_DATE $TO_DATE;;
esac