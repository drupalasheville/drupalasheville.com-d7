-- REQUIREMENTS --

Fields (Drupal core): http://drupal.org/project/drupal


-- INSTALLATION --

Install as usual, see http://drupal.org/node/895232 for further information. 


-- SUMMARY --

Semantic Fields was created to give users the means of customizing the HTML output 
of Fields. It was inspired in part by the highly recommended module Semantic 
Views (http://drupal.org/project/semanticviews) which provides the same functionality 
for Views (http://drupal.org/project/views), and as response to the "Semantic CCK" 
feature request on the CCK issue queue (http://drupal.org/node/670040).


-- BENEFITS --

With Semantic Fields enabled, users can specify the HTML elements and classes for:

	- The entire field
	- The labels -- above and inline
	- All field items
	- Each field item

This allows users to quickly create semantically rich and meaningful HTML markup 
from CCK fields such as:

	- Definition Lists
	- Ordered Lists
	- Unordered Lists

The user can also choose to remove all (or some) markup for any Field.

By facilitating semantically rich markup, Semantic Fields makes it easy for themers and
developers to increase usability, accessibility and SEO performance of Drupal sites 
without resorting to field overrides (ie. field.tpl.php).


-- CONFIGURATION & SETUP --

To use Semantic Fields, install the module and go to Structure -> Field Formats to set up the desired formats to
use when outputting fields. Once at least one field format has been created, go to the configuration form for 
each field and select a Display format for the field. Set the Display format to "Default" if you do not want to
use Semantic Fields for a particular field; the field will then be displayed using the standard Drupal field 
template.


-- USING FIELD TPL OVERRIDES --

For those instances that do require a field template override, it is recommended that 
you not use Semantic Fields for that field (ie. select the "Default" Field format). 
That way, you can simply override the field using a normal field override, and 
still have the benefits of Semantic Fields for any other fields.