// Require Node Modules
var gulp          = require('gulp'),
    browsersync   = require('browser-sync'),
    less          = require('gulp-less'),
    autoprefixer  = require('gulp-autoprefixer'),
    minifycss     = require('gulp-minify-css'),
    sourcemaps    = require('gulp-sourcemaps'),
    browsersync   = require('browser-sync'),
    reload        = browsersync.reload;

// Less Task
gulp.task('less', function() {
  gulp.src('less/style.less')
    .pipe(sourcemaps.init())
    .pipe(less())
    .pipe(autoprefixer())
    .pipe(minifycss())
    .pipe(sourcemaps.write('maps/css'))
    .pipe(gulp.dest('css'))

    // Reload browser
    .pipe(reload({stream: true}))
})

// Browser Sync
gulp.task('browser-sync', function() {
  browsersync({
    proxy: "www.drupalasheville.boi",
    port: 3000,
    ui: {
      port: 3001,
      weinre: {
        port: 3002
      }
    }
  })
})

// Watch for changes
gulp.task('watch', function(){
  gulp.watch('less/**/*', ['less'])
})

// Run run browser-sync and watch for changes
gulp.task('default', ['browser-sync', 'watch'])
