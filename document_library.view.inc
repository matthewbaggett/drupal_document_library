<?php 
function document_library_view(){
	if(document_library_check_permission('create documents')){
		if(count($_POST)){
			$document = new document();
			$document->module 			  = "document_library";
			$document->type 			    = "document";
			$document->associated_id 	= -1;
			$document->filename 		  = $_FILES['document']['name'];
			$document->description 		= $_POST['description'];
			$document->mimetype 		  = $_FILES['document']['type'];
			$document->size 			    = $_FILES['document']['size'];
			$document->uid				    = $GLOBALS['user']->uid;
      $document->sticky         = $_POST['sticky'] == "Yes" ? "Yes" : "No";


			// Encode the data before saving
			$data = file_get_contents($_FILES['document']['tmp_name']);
			$data = base64_encode($data);
			$document->data 			    = $data;

			// Call save.
			$document->save();
			$document->reload();
			$fid = $document->get_id();
			drupal_set_message("Uploaded {$document->filename}");
			drupal_goto("document_library");
		}
	}
	$view = new StdClass();
	$view->documents = document::search()
            ->order("sticky", "DESC")
						->order('created_date', 'DESC')
						->exec();
	
	// Build Breadcrumbs
	$breadcrumb = array();
	$breadcrumb[] = l(t('Home'), '<front>');
	$breadcrumb[] = l(t('Document Library'), 'document_library');
	drupal_set_breadcrumb($breadcrumb);
	
	$output = document_library_template_view(DOCUMENT_LIBRARY_ROOT_PATH . "/templates/document_library.phtml", $view);
	return $output;
}