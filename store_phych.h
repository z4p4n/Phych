#ifndef STORE_PHYCH
#define STORE_PHYCH

#define PHYCH_URL 	"192.168.1.63:81/snapshot.cgi"
#define PORT		81
#define USERPWD		"admin:0000"
#define PHYCH_SHOT	"phych.jpg"
 
/* Store last image of phych captured by Heden cam */
int store_phych (void);

#endif
