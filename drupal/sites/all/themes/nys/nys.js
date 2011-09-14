// THEME-RELATED PRESENTATIONAL JQUERY


$(document).ready(function(){
	// Hover state on anything	
	$('#search-box .form-submit, #block-nyss_blocks-global_nyss_senator_search .form-submit, #block-nyss_blocks-nyss_senator_search .form-submit, #block-nyss_blocks-nyss_signup .form-submit, #block-nyss_blocks-search_blogs .form-submit, #block-nyss_blocks-committees .form-submit, .front #content-bottom .link_live_feed, #nyss-block-issues-form .form-submit, .view-blog-search .form-submit').hover(function() {
		$(this).addClass('hover');
	}, function() {
		$(this).removeClass('hover');
	});

	$('#primary ul ul').hover(function() {
		$(this).siblings('a').addClass('hover');
	}, function() {
		$(this).siblings('a').removeClass('hover');
	});
	
	$('#block-nyss_blocks-nyss_signup input[type="text"]').focus(function() {
		if (this.value == this.defaultValue){
			this.value = '';
		}
		if(this.value != this.defaultValue){
			this.select();
		}
	});
	
	$('#block-nyss_blocks-nyss_signup input[type="text"]').blur(function() {
		if ($.trim(this.value == '')){
			this.value = (this.defaultValue ? this.defaultValue : '');
		}
	});
	
	//pops open a new window for legislative search link in primary links
	
	$(".views-table tr:last").addClass('last');
	$("#sidebar-left input.error").parent().prepend('<div class="sidebar-messages error">Missing required field.</div>').parents('body').find('.messages.error').hide();

});
