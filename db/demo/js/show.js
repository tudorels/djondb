function prepareShow() {
	var show = $("#show");

	var type = $.QueryString['type'];
	$.ajax({
		url: 'show.php?type=' + type,
		type: 'POST',
		context: document.body

	})
	.done(function(data) {
		data = jQuery.parseJSON(data);
		var table = $("<table />").appendTo(show);
		var tr = $("<tr />").appendTo(table);
		$("<th>Title</th>").appendTo(tr);
		$("<th>Price</th>").appendTo(tr);
		$("<th>Place</th>").appendTo(tr);
		$("<th>Description</th>").appendTo(tr);

		$.each(data, function(index, elem) {
			var row = $("<tr />").appendTo(table);	
			$("<td>" + elem.title + "</td>").appendTo(row);
			$("<td>" + elem.price + "</td>").appendTo(row);
			$("<td>" + elem.place + "</td>").appendTo(row);
			$("<td>" + elem.description + "</td>").appendTo(row);
		});
	});

}

$(document).ready(function() {
	prepareShow();
});
