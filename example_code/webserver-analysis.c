// -----------------------------------------------------------------------
// Webserver analysis:
// Purpose: This code reads the output generated by a typical webserver input handler
// and produces a .dot file that graphically represents interesting events.
// The .dot file can then be converted to an SVG using "dot".
// -------------------------------------------------------------------------

#include "../src/externs.h"
void setup() {
	set_input(',',"/shared/output/web.csv");
	set_graphics("/shared/output/web.dot","neato");
}
void loop() {
	add_field("server","My_Webserver");

	add_attributes("server","color=red,shape=doublecircle");
	add_attributes("reason","color=red,shape=parallelogram");
	add_attributes("file","color=blue,shape=box");

	add_composite("source_ip.country","reason file ");
	add_composite("source_ip.asn","source_ip.country reason file ");
	add_composite("source_ip","reason file ");
	add_composite("reason","file");
	if(substring("history","TOR")) add_attributes("source_ip","color=red,shape=diamond");

	add_label("source_ip"," * *.rdns history hack-type");

	draw_path("server file reason source_ip.country source_ip.asn source_ip");
}
