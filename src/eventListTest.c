#include <stdio.h>
#include <stdlib.h>
#include "eventList.h"

int main(){
	Event* head = NULL;
	head = createEvent("Asiakas saapui kauppaan", NULL);
	createEvent("Asiakas osti leipää", head);
	createEvent("Asiaskas lähti kaupasta", head);
	createEvent("Kassaneitiä, vitutti", head);
}
