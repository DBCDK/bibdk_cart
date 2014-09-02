<div id="bibdk-cart-pager">
  <?php print $variables['links']['prev']; ?>

  <?php foreach ($variables['links']['pages'] as $link): ?>
    <?php print $link; ?>
  <?php endforeach; ?>

  <?php print $variables['links']['next']; ?>
</div>