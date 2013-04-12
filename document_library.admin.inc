<?php 
function document_library_edit_document($slug){
	// Pull the TID out
	$mid_bits = explode("-", $slug, 2);
	$mid = $mid_bits[0];

	// Get the Document
	$document = document::search()->where('mid', $mid)->execOne();

	// Handle the POST
	if(count($_POST) > 0){
		if(document_library_check_permission('edit documents')){
			$document->document_heading = $_POST['document_heading'];
			$document->document_body    = $_POST['document_body'];
      $document->sticky           = $_POST['sticky'] == "Yes" ? "Yes" : "No";
			$document->save();
			drupal_set_document("Saved changes to {$document->document_heading}");
		}else{
			drupal_set_document('Cannot save changes - You do not have the "edit documents" permission');
		}
		header("Location: {$_SERVER['HTTP_REFERER']}");
		exit;
	}

	// Heading
	$output = '<h3>' . t('Document "<em>@document_geading</em>"', array('@document_geading' => $document->document_heading)) . '</h3>';

	// Get the form to change the heading & blurb
	$output.= "<form method=\"post\" action=\"\">";
	$output.= "  <fieldset>";
	$output.= "    <legend>" . t("Edit this document") . ":</legend>";
	$output.= "    <div class=\"fieldset-wrapper\">";

	$output.= "      <div class=\"form-item form-type-textfield\">";
	$output.= "        <label>" . t("Document Heading") . "</label>";
	$output.= "        <input class=\"form-text\" type=\"text\" name=\"document_heading\" value=\"{$document->document_heading}\"/>";
	$output.= "      </div>";

	$output.= "      <div classf=\"form-item form-type-textarea resizable\">";
	$output.= "        <label>" . t("Document Description") . "</label>";
	$output.= "        <div class=\"form-textarea-wrapper resizable textarea-processed resizable-textarea\">";
	$output.= "          <textarea class=\"form-textarea\" name=\"document_body\" cols=\"60\" rows=\"5\">{$document->document_body}</textarea>";
	$output.= "          <div class=\"grippie\"></div>";
	$output.= "        </div>";
	$output.= "      </div>";

  $output.= "      <div class=\"form-item form-type-radios\">";
  $output.= "        <label>" . t("Mark as Sticky?") . "</label>";
  $output.= "        <div class=\"form-radios\">";
  $output.= "          <div class=\"form-item form-type-radio\">";
  $output.= "            <input class=\"form-radio\" type=\"radio\" name=\"sticky\" value=\"Yes\" id=\"sticky_yes\" ". ($document->is_sticky()?'checked="checked"':'') . ">";
  $output.= "            <label class=\"option\" for=\"sticky_yes\">" . t("Yes") . "</label>";
  $output.= "          </div>";
  $output.= "          <div class=\"form-item form-type-radio\">";
  $output.= "            <input class=\"form-radio\" type=\"radio\" name=\"sticky\" value=\"No\" id=\"sticky_no\" " . (!$document->is_sticky()?'checked="checked"':'') . ">";
  $output.= "            <label class=\"option\" for=\"sticky_no\">" . t("No") . "</label>";
  $output.= "          </div>";
  $output.= "        </div>";
  $output.= "      </div>";

	$output.= "    </div>";
	$output.= "  </fieldset>";
	$output.= "  <div class=\"form-actions\" id=\"edit-actions\">";
	$output.= "    <input type=\"submit\" id=\"edit-submit\" name=\"op\" value=\"" . t("Save Document") . "\" class=\"form-submit\">";
	$output.= "  </div>";
	$output.= "</form>";

	if($_SERVER['HTTP_REFERER']){
		$output.= l(t("Back to Document Center"), $_SERVER['HTTP_REFERER']);
	}
	return $output;
}

function document_library_delete_document($slug){
	// Pull the TID out
	$fid_bits = explode("-", $slug, 2);
	$fid = $fid_bits[0];
	
	// Get the Document
	$document = document::search()->where('fid', $fid)->execOne();
	
	// Can't find the document? REJECT!
	if(!$document){
		drupal_set_message("No such document!", "error");
		header("Location: {$_SERVER['HTTP_REFERER']}");
		exit;
	}
	
	// Check permissions
	if(!document_library_check_permission('delete documents')){
		drupal_set_document("You lack the permission to delete this document","error");
	}else{
		drupal_set_message("Deleted {$document->filename}!");
		$document->delete();
		
	}
	header("Location: {$_SERVER['HTTP_REFERER']}");
	exit;
}
