/* ImpBadge	
 * imp_screen.c
 * serial screen buffers and whatnot
 * copyright 2018 Hack for Satan
 */

#include "imp_screen.h"

void screen_init(void) {
//	printf("\r\n");
//	printf("                         ```` `` `:-::ooshhyoo/---..`\r\n");
//	printf("                       -`     :odMNmy+yy/syhddo/+/sdmho.\r\n");
//	printf("                     /s`  `+hMMdhsdNmmdNMNMNNMo+:/::.+yMms-\r\n");
//	printf("                   `yo   odmmNMMmmmdMMMMNN++--       ` -oMMd.\r\n");
//	printf("           -+.    `y-` `ydmNmhmMMMMMMMMh+.               /MMN.\r\n");
//	printf("           . /o+./Ny  .oNNdNNmymMMMddy.                   -dNy\r\n");
//	printf("               /mMMyddNMMMMMmmmmddy/` `.-`                 `yN/\r\n");
//	printf("             `yMMMNMMMMNMMMMMMy+o/:``.:+sy/                 .hm`\r\n");
//	printf("            `mMMMdMMMMdNMMMMMMMMd-`/MMNds--..-`               sh\r\n");
//	printf("          .-yMMMNmMMNhmMMMMMMMMdy//sMMMMMMNdo+:                sy\r\n");
//	printf("           oMNNhyhNNNMMMMMMMMMmhhmyNNMMMMMMMMMm:.               +s\r\n");
//	printf("          .mMmhs/dNMMMMMMMMMMMMMMmhNMMhdMMMMMMMMd+/`             -.\r\n");
//	printf("          dMMNmNMMMNMMMMMMMMMNMMMNhdhd/NMMMMMMMMMMMMd/\r\n");
//	printf("         `yNdmNMMNNNNMMNMMNy/ohdd+ ::.-yyydhMMMMMMMMMM:\r\n");
//	printf("          -/hmMMMMMMMMNMMd:oo.`.o./md`    `mMMMMMMMMMMd`\r\n");
//	printf("           /hMMMMMMMMMNM++hms:+h/`/N/``.    .+MMMMMMMMNh:\r\n");
//	printf("           .NMMMMMMMMMM+oo:syo+--:os.:/`:     +yMMMMMMMy/:\r\n");
//	printf("           yMMMMMMMMMNms/hd+/:-:+s-.:o/+.+``   -`NMMMNMMNdh.\r\n");
//	printf("          +MMMMMMMMMMMMmMMNNNhshmh+  /syh.y/``-  hmNMNMNNNmd\r\n");
//	printf("         `mMMMMMMMMMMMMMMNMMMMMNdy-  /hmNso+..y. -dMNMMMMNMM`\r\n");
//	printf("         hMMMMMMMMMMMMMMmhNMMMMNNy++oyhmMhh.o-./` hMMMMMMMMM.\r\n");
//	printf("        .MMMMMMMMMMMMNNNNMMMMdymhohmdmNMMsNd:-` +--+mMMMMMMN`\r\n");
//	printf("        sMMMNNMMMMMNMMMNydNNMMmdNNdmdomMy/NMhy/+.::o`/dMMMM.\r\n");
//	printf("       -MNMMMNMMMMMNNNmsdhdNNmh/::o-`oyh .mmNm-hd/`:.  `/hs\r\n");
//	printf("       dMdmMMMMMMMMNMMmMMNNNN+.``    y:+ +N++hs+/o\r\n");
//	printf("      -dhooddmmMMMMMNMMmNNmm/`      +++- o/-+do/-+\r\n");
//	printf("       o-``  `:NMMMMohh---.       `:`..--:.-+//--:`\r\n");
//	printf("       ++.: -sMMMMN/+s`           `.  `-:-`/`o//  ` `\r\n");
//	printf("       .o..yNNMMdo-+-       `              `  -::  .`\r\n");
//	printf("         `.:...`./:       .  `                  ``` .\r\n");
//	printf("          -:.:---` `      .`.\r\n");
//	printf("                   `.  ...  o.\r\n");
//	printf("                   ` ../-+  -`    ` `\r\n");
//	printf("                   . .-+/``    ```\r\n");
//	printf("                   `...- -          `\r\n");
//	printf("\r\n");
}

void screen_print() {
	unsigned char num_options = 3;
	printf("%s\r\n", rpg_get_state_description(rpg_state));
	printf("\r\n");
	strcpy(rpg_options[0], rpg_0_opts[0]);
	strcpy(rpg_options[1], rpg_0_opts[1]);
	strcpy(rpg_options[2], rpg_0_opts[2]);

	for (char i = 0; i < num_options; i++) {
		if (selected_option == i) printf("-> ");
		else printf("   ");
		printf("%s\r\n", rpg_options[i]);
	}	
}