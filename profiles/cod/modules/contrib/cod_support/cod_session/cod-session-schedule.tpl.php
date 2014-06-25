<?php if(!empty($days) && !empty($rooms) && !empty($arranged_slots)): ?>
<?php foreach ($days as $day_key => $day_title): ?>
  <div class="session-day" id="sessions-<?php print $day_key; ?>">
  <h2><?php print $day_title; ?></h2>
  <?php if ($schedule_display == 0): ?>
    <table class="session-calendar multi-column-schedule">
      <?php foreach ($arranged_slots[$day_key] as $slot): ?>
      <tr class="<?php print $zebra = $zebra == 'even' ? 'odd':'even'; ?> <?php print $slot['class']; ?>">
        <td class="time-label">
          <?php print $slot['start']; ?>&nbsp;-<br /><?php print $slot['end']; ?>
        </td>
        <td>
        <?php foreach($schedule_grid[$day_key][$slot['nid']] as $room_key => $schedule_room): ?>
          <?php if (!empty($schedule_room['sessions'])): ?>
          <div class="schedule-room-<?php print $room_key; ?> <?php print $schedule_room['class']; ?>">
            <?php foreach($schedule_room['sessions'] as $session): ?>
              <div class="views-item type-<?php print check_plain($session['session']->type); ?>">
              <?php print $view_results[$session['session']->nid]; ?>
              </div>
            <?php endforeach; ?>
            <?php // Room availability if set.
            if (isset($schedule_grid[$day_key][$slot['nid']][$room_key]['availability'])): ?>
              <div><?php print $schedule_grid[$day_key][$slot['nid']][$room_key]['availability']; ?></div>
            <?php endif ?>
            <?php // Schedule call-to-action if set.
            if (isset($schedule_grid[$day_key][$slot['nid']][$room_key]['cta'])): ?>
              <div><?php print $schedule_grid[$day_key][$slot['nid']][$room_key]['cta']; ?></div>
            <?php endif ?>
          </div>
          <?php elseif (!$schedule_grid[$day_key][$slot['nid']][$room_key]['spanned'] && $show_rooms[$day_key][$room_key]): ?>
            <?php // Room availability if set.
            if (isset($schedule_grid[$day_key][$slot['nid']][$room_key]['availability'])): ?>
              <div><?php print $schedule_grid[$day_key][$slot['nid']][$room_key]['availability']; ?></div>
            <?php endif ?>
            <?php // Schedule call-to-action if set.
            if (isset($schedule_grid[$day_key][$slot['nid']][$room_key]['cta'])): ?>
              <div><?php print $schedule_grid[$day_key][$slot['nid']][$room_key]['cta']; ?></div>
            <?php endif ?>
          <?php endif; ?>
          <div class="schedule-room-title"><?php print $rooms[$room_key]['title']; ?></div>
        <?php endforeach ?>
        </td>
      </tr>
      <?php endforeach; ?>
    </table>
  <?php endif; ?>
  <?php if ($schedule_display == 1): ?>
    <table class="session-calendar multi-column-schedule">
      <tr>
        <th><?php print t('Time'); ?></th>
        <?php foreach ($rooms as $room_nid => $room): ?>
        <?php if ($show_rooms[$day_key][$room_nid]): ?>
          <th><span class="room-label"><?php print $room['title']; ?></span><?php if(!empty($room['sponsor'])): ?><div class="sponsor-label"><?php print $room['sponsor']; ?></div><?php endif; ?></th>
        <?php endif; ?>
        <?php endforeach ?>
      </tr>
      <?php foreach ($arranged_slots[$day_key] as $slot): ?>
      <tr class="<?php print $zebra = $zebra == 'even' ? 'odd':'even'; ?> <?php print $slot['class']; ?>">
          <td class="time-label">
            <?php print $slot['start']; ?>&nbsp;-<br /><?php print $slot['end']; ?>
          </td>
          <?php foreach ($room_nids as $room_nid): ?>
            <?php if (!empty($schedule_grid[$day_key][$slot['nid']][$room_nid])): ?>
              <?php // Are there scheduled items to print in this cell?
              if (!empty($schedule_grid[$day_key][$slot['nid']][$room_nid]['sessions'])): ?>
                <td class="session occupied<?php print $schedule_grid[$day_key][$slot['nid']][$room_nid]['class']; ?>" colspan="<?php print $schedule_grid[$day_key][$slot['nid']][$room_nid]['colspan']; ?>">
                <?php foreach($schedule_grid[$day_key][$slot['nid']][$room_nid]['sessions'] as $session): ?>
                  <div class="views-item type-<?php print check_plain($session['session']->type); ?>">
                  <?php print $view_results[$session['session']->nid]; ?>
                  </div>
                <?php endforeach ?>
                <?php // Room availability if set.
                if (isset($schedule_grid[$day_key][$slot['nid']][$room_nid]['availability'])): ?>
                  <div><?php print $schedule_grid[$day_key][$slot['nid']][$room_nid]['availability']; ?></div>
                <?php endif ?>
                <?php // Cell call-to-action if set.
                if (isset($schedule_grid[$day_key][$slot['nid']][$room_nid]['cta'])): ?>
                  <div><?php print $schedule_grid[$day_key][$slot['nid']][$room_nid]['cta']; ?></div>
                <?php endif ?>
              <?php // Print a cell if it's not being spanned.
              elseif (!$schedule_grid[$day_key][$slot['nid']][$room_nid]['spanned'] && $show_rooms[$day_key][$room_nid]): ?>
                <td class="session empty">&nbsp;
                <?php // Room availability if set.
                if (isset($schedule_grid[$day_key][$slot['nid']][$room_nid]['availability'])): ?>
                  <div><?php print $schedule_grid[$day_key][$slot['nid']][$room_nid]['availability']; ?></div>
                <?php endif ?>
                <?php // Cell call-to-action if set.
                if (isset($schedule_grid[$day_key][$slot['nid']][$room_nid]['cta'])): ?>
                  <div><?php print $schedule_grid[$day_key][$slot['nid']][$room_nid]['cta']; ?></div>
                <?php endif ?>
              <?php endif ?>
              <?php // Only end the table cell if there were items or spanning.
              if (!empty($schedule_grid[$day_key][$slot['nid']][$room_nid]['sessions']) || !$schedule_grid[$day_key][$slot['nid']][$room_nid]['spanned']): ?>
                </td>
              <?php endif ?>
            <?php endif ?>
          <?php endforeach ?>
      </tr>
      <?php endforeach ?>
    </table>
  <?php endif; ?>
  </div>
<?php endforeach ?>
<?php endif ?>
