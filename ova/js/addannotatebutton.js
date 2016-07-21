//Options to load in Open Video Annotation, for all the plugins
(function($, Drupal, undefined){
var resource_entity_id = drupalSettings.ova_annotation.annotation_settings;
var options = {
        optionsAnnotator: {
            permissions: {},
            //auth: {tokenUrl:'http://catch.aws.af.cm/annotator/token'},
            store: {
                // The endpoint of the store on your server.
                prefix: window.location.protocol + "//" + window.location.host + '/annotation-store/api',

                annotationData: {
                    //uri: 'http://danielcebrian.com/annotations/demo.html'
                    uri: window.location.href
                },
                loadFromSearch: {
                    limit: 10000,
                    resource_entity_id: resource_entity_id,
                    uri: window.location.href
                },
                urls: {
                  // These are the default URLs.
                  create:  '/annotations/',
                  update:  '/annotations/:id',
                  destroy: '/annotations/:id',
                  search:  '/search'
                }
            },
            richText: {
                tinymce: {
                    selector: "li.annotator-item textarea",
                    plugins: "media image insertdatetime link code",
                    menubar: false,
                    toolbar_items_size: 'small',
                    extended_valid_elements: "iframe[src|frameborder|style|scrolling|class|width|height|name|align|id]",
                    toolbar: "insertfile undo redo | styleselect | bold italic | alignleft aligncenter alignright alignjustify | bullist numlist outdent indent | link image media rubric | code "
                }
            },
            share: {}, //Share plugin
            annotator: {} //Annotator core
        },
        optionsVideoJS: {
            techOrder: ["html5", "flash", "youtube"]
        },
        optionsRS: {},
        optionsOVA: {
            posBigNew: 'none' /*,NumAnnotations:20*/
        }
}
    //Load the plugin Open Video Annotation
var ova = new OpenVideoAnnotation.Annotator($('#airlock'), options);
//change the user (Experimental)
ova.setCurrentUser($('#username').val());
$('#username').change(function() {
    ova.setCurrentUser($(this).val());
});

})(jQuery, Drupal);