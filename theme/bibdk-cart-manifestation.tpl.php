<article class="manifestation clearfix cart-item-id-<?php print $id; ?>">
    <div class="actions">

        <div class="primary-actions">
            <div class="btn-wrapper">
              <?php print drupal_render($fields['bibdk_mani_reservation_button']); ?>
            </div>
        </div>
        <div class="secondary-actions">
            <ul>
              <?php print drupal_render($fields['bibdk_cart_manifestation_link']); ?>
            </ul>
        </div>
    </div>
    <!-- .actions -->
    <div class="manifestation-data text">
        <h3><?php print $title; ?></h3>
        <h3><?php print $author; ?></h3>
        <table>
            <tbody>
            <?php print drupal_render($fields); ?>
            </tbody>
        </table>
    </div>
</article>
