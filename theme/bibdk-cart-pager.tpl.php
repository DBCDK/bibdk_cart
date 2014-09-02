<div id="bibdk_cart_pager">
  <?php print $variables['links']['first']; ?>
  <?php print $variables['links']['prev']; ?>

  <?php foreach ($variables['links']['pages'] as $link): ?>
    <?php print $link; ?>
  <?php endforeach; ?>

  <?php print $variables['links']['next']; ?>
  <?php print $variables['links']['last']; ?>
</div>