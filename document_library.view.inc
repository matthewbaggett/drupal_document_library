<?php 
function document_library_view(){
	if(count($_POST)){
		$document = new document();
		$document->module 			= "document_library";
		$document->type 			= "document";
		$document->associated_id 	= -1;
		$document->filename 		= $_FILES['document']['name'];
		$document->data 			= file_get_contents($_FILES['document']['tmp_name']);
		$document->mimetype 		= $_FILES['document']['type'];
		$document->size 			= $_FILES['document']['size'];
		$document->uid				= $GLOBALS['user']->uid;
		$document->save();
		$document->reload();
		$fid = $document->get_id();
		drupal_set_message("Uploaded {$document->filename}");
		drupal_goto("document_library");
	}
	$view = new StdClass();
	$view->documents = document::search()
						->order('filename', 'ASC')
						->exec();
	$output = document_library_template_view(DOCUMENT_LIBRARY_ROOT_PATH . "/templates/document_library.phtml", $view);
	return $output;
}