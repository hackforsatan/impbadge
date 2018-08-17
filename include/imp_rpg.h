/* ImpBadge	
 * imp_rpg.h
 * text constants for ImpBadge rpg
 * copyright 2018 Hack for Satan
 */

#ifndef IMP_RPG_H
#define	IMP_RPG_H

#include "imp_usart.h"
#include "imp_config.h"

#include <xc.h>
#include <string.h>

/* types */
typedef enum {
	RPG_0, RPG_0_0, RPG_0_1, RPG_0_2, RPG_0_0_0, RPG_0_0_1,
    RPG_0_1_0, RPG_0_1_1, RPG_0_2_0, RPG_0_2_1, RPG_1, RPG_1_0,
    RPG_1_1, RPG_1_1_0, RPG_1_1_1, RPG_1_1_1_0, RPG_1_1_1_1, RPG_1_1_1_2,
    RPG_2, RPG_2_0, RPG_2_1, RPG_2_1_0, RPG_2_1_1, RPG_3,
    RPG_3_0, RPG_3_1, RPG_3_1_0, RPG_3_1_1, RPG_3_1_2, RPG_4, RPG_TRIGGER,
    RPG_KEY, RPG_CUTTERS, RPG_HAMMER, RPG_ROPE
} rpg_state_t;

/* globals */
rpg_state_t rpg_state = RPG_TRIGGER;
unsigned char rpg_unlocked_items = 0;
unsigned char rpg_num_opts = 0;
unsigned char rpg_options[8][64];
unsigned char selected_option = 0;
unsigned char rpg_show_inventory = 0;

/* function prototypes */
void rpg_print_desc(void);
void rpg_print_opts(void);
char const *rpg_get_state_description(rpg_state_t);
rpg_state_t rpg_get_next_state(unsigned char);

const char * const rpg_items[] = {"key", "bolt cutters", "hammer", "rope", 0};

/* Trigger Warning */
const char *rpg_trigger = 
//"WARNING: The following text adventure is pretty fucked up. If you have a\r\n"
//"trigger just assume it's in here. Touch [scry] to return to the badge menu at\r\n"
//"any time; touch [sacrifice] to continue.";
"                            ______________ _________\r\n"
"                           /____ _________\\`.______]\r\n"
"                          _`|Mosier State Hospital|_____\r\n"
"                       ._;:/|_________   _________|_____]\r\n"
"                       \"\\:*,| |_#_#_#_\\_/_#_#_#_| |##| |\r\n"
"                       | |\\!| |_#_x_x_| |_x_#_#_| |#x| |\r\n"
"                       |  __  |_________________|  __  |\r\n"
"                       | |#x| |=================| |xx| |\r\n"
"                      ,| |xx| ||||||||[X]|||||||| |xx| |\r\n"
"                    .;/|______|_______| |_______|______|,.\r\n"
"+^+            +^+            +^+     | |     +^+            +^+            +^+\r\n"
"| |------------| |------------| |--[.......]--| |------------| |------------| |\r\n"
"| |------------| |------------| |--[|||||||]--| |------------| |------------| |\r\n"
"|_|------------|_|------------|_|--[''''''']--|_|------------|_|------------|_|\r\n"                                                                                                                                                      
"     @@@         &@@@@@@.  /@@@      @@@ @@@@       @@@    .@@@   @@@,     .@@@\r\n"                      
"    @@@@@      @@@@@@@@@@. @@@@@    @@@@ @@@@      @@@@%   @@@@@ #@@@@)    (@@@\r\n"                       
"   @@@@@@@    (@@@@@/  `%) (@@@@@\\(@@@@@ @@@@      @@@@@   @@@@@ @@@@@@( @@@@@%\r\n"                        
"  @@@@@@@@#   &@@@@      `  .@@@@@@@@@@  @@@@      @@@@@   @@@@@ @@@@@@@@@@@@@#\r\n"                      
" @@@@/ @@@@#  (@@@@@@@@@@*   .@@@@@@@%   @@@@      @@@@@   @@@@@ @@@(@@@@@(@@@&\r\n"                       
"@@@@/__@@@@@*  `&@@@@@@@@@)   .@@@@@@    @@@@      @@@@@   @@@@@ %@@  @@@@ @@@@\r\n"                       
"@@@@@@@@@@@@@         /@@@%    @@@@@&    @@@@.     @@@@@. ,@@@@@ \\@@   @%? `@@&\r\n"                        
"@@@@@   \\@@@@  @@@@@@@@@@@@    \\@@@@@    @@@@@@@@& @@@@@@@@@@@@@  @@.  @%?  @@%\r\n"                        
"@@@.     @@@@   @@@@&&@@@@      `@@@@    @@@@@@@@@ `@@@@@@@@@@@@  (@   /@   @@,\r\n"                     
"%@(      `@@@    @@@  @@@,       `@@,    `@@@? `@@   @@@?   @@@.  `@,  `@   `@,\r\n"                      
"@(        @@?     @\\ `&@@         @@      .@@   `@   `@@%   @@&;   @#    `   @(\r\n"                        
"@;        @@      &@  `@@         ;@      .@@    @    `@@   %@@    &&    ?   @&\r\n"                      
"@%        @@      *@.  `@         (@.     .%@    &     &@?  `@,    %@        @?\r\n"                       
"@@        @@       @,   @         /@,      %@          .@    `     (@        @)\r\n"                       
"(@        `@       &@   @,        `@/      `@          .@           &;       @\r\n"                     
"`@         `       `&    `         `@       $           $                    %\r\n"
"Touch [scry] to return to the badge menu at any time; touch [sacrifice] to\r\n"
"continue.";
                                                                                                                                                 
                         
                                                                                                                                

const char * const rpg_trigger_opts[] = {"Continue", 0};

/* 0: ROOM 0 */
const char *rpg_0 =
"It's dark and it's cold. The sunlight creeping through the wood planks over the\r\n"
"windows is barely enough to make out the sign on the far wall--Mosier State\r\n"
"Hospital. The place is a goddamn mess. Should've just leveled it and built a\r\n"
"strip mall. You can see doors to the left and right and one straight ahead.\r\n"
"You've really got your work cut out for you, that's for sure, but the rent\r\n"
"don't pay itself. You flip on your headlamp, hoist up your toolbox, and wish\r\n"
"to Christ you had a drink right now.";

const char * const rpg_0_opts[] = {"Left", "Right", "Ahead", 0};

/* 0_0: Left */
const char *rpg_0_0 =
"Looks empty. The walls are bare concrete spattered black in places, like\r\n"
"someone sloshed a bucket of paint around the room. Locker room, maybe? Or the\r\n"
"place they used to spray down the inmates for lice. No windows, just a big\r\n"
"wooden door at the far end of the room. Your boot bumps something and it\r\n"
"clatters across the floor.";

const char * const rpg_0_0_opts[] = {"Inspect object", "Inspect door", 0};

/* 0_0_0: Inspect object */
const char *rpg_0_0_0 =
"It's a syringe. The big, old-timey kind you see in the movies. It's rusty and\r\n"
"the needle's a little bent, but it's intact. You shake it and--I'll be damned.\r\n"
"It's been, what, 60 years since this place shut down? Wonder what kind of\r\n"
"fucked-up cocktail they were givin' those nutjobs. You give the plunger a light\r\n"
"push and a drop of godknowswhat squirts out the tip. I'll be damned. You find a\r\n"
"vein easily and give it a slap. The crooked needle still sticks. What are you\r\n"
"doing? You push the plunger all the way. You'll be damned.";

const char * const rpg_0_0_0_opts[] = {"Continue", 0};

/* 0_0_1: Inspect door */
const char *rpg_0_0_1 =
"It looks out of place in here. Better fit for a castle than a nuthouse. It's\r\n"
"locked by a sliding bolt. Storage, maybe? Something's scratched into the wood\r\n"
"under the handle. NONE ABOVE. NONE BELOW. ALL OF THEM HERE. Whatever the fuck\r\n"
"that means. It takes some oil and a wrench but the bolt pops and the door\r\n"
"creaks open. It's pitch black inside. You flip your headlamp up to full brights\r\n"
"and see the walls. High walls. Impossibly high. Right? They're covered floor-up\r\n"
"in scratched words, the same four words, over and over, disappearing into the\r\n"
"black void where a ceiling should be. ALL OF THEM HERE. ALL OF THEM HERE. \"I'm\r\n"
"an angel...\" A whisper. A woman. Where? The door slams behind you and the\r\n"
"headlamp goes dark. \"Can't you see my wings?\" You can't see anything at all.\r\n"
"Who's there?! \"You'll be an angel too! I know how!\" Your vision goes white\r\n"
"from the pain. \"Isn't it wonderful?\" You can hear the peeling. \"Isn't Heaven\r\n"
"so bright?\"";

const char * const rpg_0_0_1_opts[] = {"Continue", 0};

/* 0_1: Right */
const char *rpg_0_1 =
"Some kind of waiting room. Smells like rancid meat. It's swarming with flies.\r\n"
"There's a couple of chairs, a small mirror on the wall, and an animal carcass\r\n"
"rotting in the corner.";

const char * const rpg_0_1_opts[] = {"Inspect mirror", "Inspect carcass", 0};

/* 0_1_0: Inspect mirror */
const char *rpg_0_1_0 =
"It's so caked in dust you can't even see a reflection. You wipe it down with\r\n"
"your rag and see yourself through the hairline cracks and streaks of filth.\r\n"
"You see your wife. You see her fucking him in your bed. You see your son\r\n"
"telling his friends you're a doctor. Telling them you died in the war. You can\r\n"
"see yourself on the motel floor cradling an empty bottle of Beam. The phone's\r\n"
"ringing. You didn't wake up. You didn't even know she was gone, did you? You\r\n"
"can see yourself the way they see you. Hairline cracks and streaks of filth.\r\n"
"The mirror shatters on your fist and your fist shatters on the wall behind it.\r\n"
"You pick up a shard from the ground and see them in it, happy. You drag the\r\n"
"business end from wrist to elbow, close your eyes, and lie down in the filth.\r\n"
"Where you belong";

const char * const rpg_0_1_0_opts[] = {"Continue", 0};

/* 0_1_1: Inspect carcass */
const char *rpg_0_1_1 =
"It's a cat. God, it smells. Here, kitty kitty. The flies cover it like a burial\r\n"
"shroud. Good kitty. Fetal kittens litter the floor around it, pink and\r\n"
"deformed, black with flies. Such a good kitty, yes you are. I could just eat\r\n"
"you up, yes I could! I could just eat you allll up! Your stomach feels like\r\n"
"it's going to burst. You shove your finger down your throat and vomit on the\r\n"
"carcass to make more room. Full again. Toolbox. Hacksaw. Good kitty. Start at\r\n"
"the sternum and work your way to the groin. You watch the guts pour onto the\r\n"
"floor. Room for seconds. You get lightheaded from the blood loss but you can't\r\n"
"stop eating. The chewed bits slide out from under your ribcage. You pop them\r\n"
"back into your mouth. Good kitty. Such a good--";

const char * const rpg_0_1_1_opts[] = {"Continue", 0};


/* 0_2: Ahead */
const char *rpg_0_2 =
"Judging by the rows of folding chairs and the 3-foot crucifix on the wall, this\r\n"
"used to be a chapel. To the left of the pulpit there's a crudely cut hole in\r\n"
"the wall with HOME scrawled above it in crayon.";

const char * const rpg_0_2_opts[] = {"Inspect crucifix", "Inspect hole", 0};

/* 0_2_0: Inspect crucifix */
const char *rpg_0_2_0 =
"You've gotta give the sculptor credit for detail. The contortion of the face\r\n"
"The anguish in the eyes. The streams of blood tracing perfect contours over the\r\n"
"torn body, pouring from the thorns, the riven torso, the teeth, the eyes, the\r\n"
"ears, the cock. The realism is striking. There's blood everywhere. The little\r\n"
"girl in the front pew says \"They call it a sacrifice to God, mister. But they\r\n"
"don't believe in God, mister...\" You can barely see the cross beneath all the\r\n"
"blood. There's no face or body at all. Just blood. Everywhere. The girl isn't\r\n"
"there and she asks \"What would Jesus do, mister?\" Fucking bleed.";

const char * const rpg_0_2_0_opts[] = {"Continue", 0};

/* 0_2_1: Inspect hole */
const char *rpg_0_2_1 =
"It's about two feet in diameter, cut jagged into the drywall. Even on full\r\n"
"blast your headlamp can't cut the darkness inside. You crawl through. CREAK\r\n"
"CLANK CLICK. Behind you. You struggle to flip onto your back. The hole is gone.\r\n"
"It's a small metal door with a glass window. There's a man in a white coat on\r\n"
"the other side. You can see his face. He's scribbling on a clipboard. The walls\r\n"
"around you are ventilated metal. He clicks his pen. He's humming. It's\r\n"
"familiar. He's got the little bitter baby in His hands ... HEY! HEY! LET ME OUT\r\n"
"OF HERE! He can't hear you. He puts the clipboard down and presses a button.\r\n"
"Flames explode beneath you. He's got the whole world right in His hands.\r\n"
"HELP!!! He can hear you. He just likes to watch.";

const char * const rpg_0_2_1_opts[] = {"Continue", 0};

/* 1: Metal cabinet */
const char *rpg_1 =
"There are no windows or doors, just a metal cabinet on the wall and a gun on\r\n"
"the floor. Rats crawl into the room through a large crack in the corner. They\r\n"
"look hungry.";

const char * const rpg_1_opts[] = {"Inspect gun", "Inspect cabinet", 0};

/* 1_0: Inspect gun */
const char *rpg_1_0 =
"It's old, antique. Might be worth something. There's still a round in the\r\n"
"chamber. You give the cylinder a spin and snap it back into place. Reminds you\r\n"
"of Pop's old pistol. He never did take you shooting. Never did nothin', just\r\n"
"drank. You put it to your temple, cock the hammer, and pull the trigger. CLICK.\r\n"
"You pop the chamber, spin it. The barrel burns your face. Just drank and hit\r\n"
"Mom. Hit her til she screamed. Til she spit teeth on the kitchen floor. You\r\n"
"kept one under your pillow. A part of her you'd always have in case... Cock.\r\n"
"Pull. CLICK. Spin. Cancer got her first, so he started hittin' you instead. Hit\r\n"
"you til your skull fractured and you ran off for good. Cock. Pull. CLICK. Spin.\r\n"
"He didn't have nobody left to hit, so he did right by the world and blew his\r\n"
"fuckin' brains out in a shed. Cock. Pull. CLICK. I just want to make you proud,\r\n"
"Pop. Just once. I gotta do right, Pop. Spin. Cock. Just like you. Pull.";

const char * const rpg_1_0_opts[] = {"Continue", 0};

/* 1_1: Inspect cabinet */
const char *rpg_1_1 =
"It's a rectangular cabinet box about 2 feet tall, 1 foot wide, dented, rusty,\r\n"
"locked.";

const char * const rpg_1_1_opts[] = {"Pry", 0};

/* 1_1_0: Pry */
const char *rpg_1_1_0 =
"You wedge a screwdriver beneath the lock and lean into it hard. The box crashes\r\n"
"to the ground exposing a hole in the wall. Rats swarm out of it, starving.\r\n"
"You're up to your shins in a writhing mass of fur, teeth, disease, climbing up\r\n"
"your legs, ripping at your clothes, flesh. You're transfixed on the hole and\r\n"
"the unending blackness beyond. You can't help but smile. It's made of skin.\r\n"
"Just like us.";

const char * const rpg_1_1_0_opts[] = {"Continue", 0};

/* 1_1_1: Use key (Secret) */
const char *rpg_1_1_1 =
"It opens. There's a breaker switch inside. A strip of masking tape above it\r\n"
"says MATTHEW 14:16. You flip the switch and hear a rumbling sound from beneath\r\n"
"the floor. Do you have a migraine? Am I having a stroke? They're hungry, you\r\n"
"know. I know.";

const char * const rpg_1_1_1_opts[] = {"Embrace", "Take control", 0};

/* 1_1_1_0: Embrace */
const char *rpg_1_1_1_0 =
"This is forever. This is all there is. You lie on your back, close your eyes,\r\n"
"and let the rats become one with all you ever were. All you'll ever be.";

const char * const rpg_1_1_1_0_opts[] = {"Continue", 0};

/* 1_1_1_1: Take control */
const char *rpg_1_1_1_1 =
"You can still see flashes of the revolver beneath the swarming rats. You lunge\r\n"
"for it and shove the cold barrel into the soft flesh beneath your chin. I'm\r\n"
"coming home, Pop. Where we belong. Cock. Pull.";

const char * const rpg_1_1_1_1_opts[] = {"Continue", 0};

/* 1_1_1_2: Use bolt cutters (Secret) */
const char *rpg_1_1_1_2 =
"The poor things are famished, just skin and bone. You pull off your work boots\r\n"
"and socks, stretch out your feet, and take out the bolt cutters. Just skin and\r\n"
"bone. Looking up to the heavens, He gave thanks and broke the loaves. One\r\n"
"little piggy? SNAP. Two little piggy? SNAP. They all ate and were satisfied.\r\n"
"The floor rumbles again. The rats scatter as you hear a soft CRACK followed by\r\n"
"a very loud one, then an overwhelming nothing.";

const char * const rpg_1_1_1_2_opts[] = {"Continue", 0};

/* 2: Cots */
const char *rpg_2 =
"It's dark and it's cold. You're lying on a cot--one of many crammed in the tiny\r\n"
"room, all of them occupied by men in hospital gowns, asleep. Or dead. The only\r\n"
"light comes from a small window in the door across the room. Your toolbox is on\r\n"
"the floor next to you. CLANG. It's coming from the hallway outside. CLANG.\r\n"
"Someone beating on the wall. Closer. CLANG. \"Heeeere, boy!\" CLANG. \"Who's\r\n"
"gonna be my good lil' boy tonight?\" Shadows near the window. CLANG! You sit up\r\n"
"and catch the wide-eyes of an old man in the cot next to yours. He motions for\r\n"
"you to lie down. \"The burning men won't choose you if you're asleep like a\r\n"
"good boy.\" CLANG. He shuts his eyes. \"Please don't scream, mister. They like\r\n"
"it when it you scream.\"";

const char * const rpg_2_opts[] = {"Don't move", "Run", 0};

/* 2_0: Don't move */
const char *rpg_2_0 =
"You roll over with your back to the door, push your toolbox under the bed, and\r\n"
"pull the blanket over you. CLANG. CLICK. CREAK. Light pours into the room as\r\n"
"the door swings open. \"Look at all these good, good boys!\" He's dragging\r\n"
"something along the ground as he walks through the rows of cots. You shut your\r\n"
"eyes tight. The dragging stops. \"Good boyyyyy.\" a whisper so close to your\r\n"
"face, you can feel his spit on your lips. A hand grabs your shoulder and rolls\r\n"
"you onto your back. You open your eyes just in time to see the metal pipe--";

const char * const rpg_2_0_opts[] = {"Continue", 0};

/* 2_1: Run */
const char *rpg_2_1 =
"You jump to your feet and grab the toolbox. CLANG. \"Bad,\" the old man\r\n"
"whispers. You move quickly and quietly to the door. CLANG. A shadow darkens the\r\n"
"window. You freeze. CLANG. The door rattles. Don't breathe. The shadow\r\n"
"disappears. CLANG. He's moving on. Now's your chance. A frail, cold hand grabs\r\n"
"your wrist. You shake it loose and look at the man, or what's left of him. His\r\n"
"ears and nose are gone. Surgically. Stitched. Both legs amputated at the knee.\r\n"
"\"They killed her and burned her...\"";

const char * const rpg_2_1_opts[] = {"Shut up", 0};

/* 2_1_0: Shut up */
const char *rpg_2_1_0 =
"You put your finger to your lips. \"They killed her and burned her! THEY KILLED\r\n"
"HER AND BURNED HER!\" Fuck. Shadows outside. CLANG! CLICK. The door swings open\r\n"
"and the light blinds you. \"THEY KILLED HER AND BURNED HER!\" Good boy.";

const char * const rpg_2_1_0_opts[] = {"Continue", 0};

/* 2_1_1: Use hammer (Secret) */
const char *rpg_2_1_1 = 
"You move fast, shoving your hand over the man's mouth. You pull the hammer out\r\n"
"of your toolbox and bring it down hard. The screaming in your head drowns out\r\n"
"the crack of bones. Thank God. Again! This isn't you. Again! It's self-defense.\r\n"
"Again! It's murder. Again! It's survival. Again! AGAIN! AGAIN! AGAIN! Until the\r\n"
"hammer's too slippery to hold. CLANK. Farther down the hall. Clank. He's gone.\r\n"
"Thank God. You wipe your hand on the man's gown and head for the door. The\r\n"
"handle turns. Thank God.";

const char * const rpg_2_1_1_opts[] = {"Go to hallway", 0};

/* 3: Hallway */
const char *rpg_3 =
"You walk out into a well-lit hallway bustling with people. What the ... fuck? A\r\n"
"man with a clipboard is coming down the hall, flanked by nurses. \"There's a\r\n"
"transfer arriving and we need 17 beds cleared by morning. Incinerators up?\"\r\n"
"Yes, doctor. \"Good. Cull a few from East Wing. Prioritize the infirm. Let Butch\r\n"
"do the rest. It's his birthday, after all.\" Yes, doctor. He sees you. You\r\n"
"freeze. \"Ah, Maintenance, perfect timing. That wall marker has lost a screw.\"\r\n"
"He points to a crooked sign down the hall--STAIRWELL--then returns to the\r\n"
"clipboard as he and the nurses continue down the hallway. \"Pamela, be a dear\r\n"
"and ask Dr. Heinze if he needs some test subjects.\" Yes, doctor.";

const char * const rpg_3_opts[] = {"Fix sign", "Enter stairwell", 0};

/* 3_0: Fix sign */
const char *rpg_3_0 =
"This isn't real. This is a dream. They shuttered this shithole 60 years ago.\r\n"
"Take a breath. Slow. You dig in the toolbox for a bolt that'll fit. You know\r\n"
"people died here. Take a breath. Slow. You find a bolt and twist it into the\r\n"
"hole. Someone on a lower floor is screaming. Take a breath. People died here.\r\n"
"Slow. A nurse points at you and whispers to another. Just fix the damn sign.\r\n"
"\"Excuse me, sir.\" You look up and see a man standing over you. Take a brea--\r\n"
"He jams a syringe into your throat. \"Shhhh... Slow...\"";

const char * const rpg_3_0_opts[] = {"Continue", 0};

/* 3_1: Enter stairwell */
const char *rpg_3_1 =
"You keep your head down and pretend to dig through your box for tools. The sign\r\n"
"says SANCTUARY now. Just act like you know what you're doing. You grab the\r\n"
"handle and crack the door. The sign says STAIRWELL again. Fuck this place. You\r\n"
"slip through the door and shut it behind you. No one saw you. \"Can you see\r\n"
"them?\" You spin around and see a man sitting on the landing below, covering\r\n"
"his face with his hands. He snaps his head up in your direction but keeps one\r\n"
"hand over his eyes. \"The shadows. On the walls! Can you see them?\" His mouth\r\n"
"hangs open on the last word. A silent scream. The harsh glow of the fluorescent\r\n"
"lights seeps into every crack and corner. There are no shadows. \"They're\r\n"
"inside us you know.\" His mouth is closed. His hand falls limp from his face,\r\n"
"exposing the blood-crusted chasms where his eyes used to be. \"Why won't they\r\n"
"let us die?\"";

const char * const rpg_3_1_opts[] = {"Downstairs", "Hallway", 0};

/* 3_1_0: Downstairs */
const char *rpg_3_1_0 =
"The flight below is nothing but darkness. You can still hear him. \"It's too\r\n"
"late, you know. They've already found God. And He'll find you too.\" The air\r\n"
"tastes like rust. You hear the sickening snap of bone and the crumpling of his\r\n"
"body. The lights flicker and burst in plumes of glistening dust. It's\r\n"
"beautiful, in a way. You're not sure if it's the falling shadows or the glass\r\n"
"in your eyes but--";

const char * const rpg_3_1_0_opts[] = {"Continue", 0};

/* 3_1_1: Hallway */
const char *rpg_3_1_1 =
"The handle won't turn. You spin around to find the man standing only inches\r\n"
"from your face. Flies are crawling out of the black holes in his skull and he's\r\n"
"fucking smiling. Your stomach turns and you puke in his face, into his gaping\r\n"
"sockets, his grinning mouth, chest, shoes. He grabs your shoulders and forces\r\n"
"you back up. Forces you to look. \"You can see them, can't you?\" No. No, I\r\n"
"won't! You have to pull hard to get the screwdriver out of your eye socket.\r\n"
"\"This is forever.\" Fucking smiling ... You shove the screwdriver into the\r\n"
"other eye, and finally--";

const char * const rpg_3_1_1_opts[] = {"Continue", 0};

/* 3_1_2: Use rope (Secret) */
const char *rpg_3_1_2 =
"Tying a noose is harder than you thought, so you just coil the rope around his\r\n"
"neck like thread on a spindle. He cracks a smile--a bright contrast to the deep\r\n"
"blackness of the holes in his skull. \"This is forever. This is all there is.\"\r\n"
"He's touching himself. You cinch the rope. His ribs crack as you shove him over\r\n"
"the railing. His spine cracks next. You watch the rope swing, alight in the\r\n"
"flickering fluorescent un-color of disease. When the rope goes still, you go\r\n"
"downstairs and open the door.";

const char * const rpg_3_1_2_opts[] = {"Go to surgery room", 0};

/* 4: Basement */
const char *rpg_4 =
"The basement's awash in the orange glow of flames from three incinerators. Men\r\n"
"in white coats pull bodies out of laundry bins and dump them into the fires.\r\n"
"\"Beautiful isn't it?\" You turn and see a man you've seen before. A doctor.\r\n"
"\"We need 17 tonight. Your choice.\" He pats you on the shoulder and smiles.\r\n"
"\"Happy birthday, Butch.\" You look down at the thick lead pipe in your hand--\r\n"
"your good fuckin' boy. You open the stairwell door and--\r\n"
"===============================================================================\r\n"
"Badge is complete. New item unlocked in blinky mode. Hail Satan.\r\n";

const char * const rpg_4_opts[] = {"Continue", 0};

const char *rpg_key =
"You lick the oily key up and down. It's fucking delicious. Suck on it. God,\r\n"
"yes. Swallow it. Keep trying. It's stuck. Keep trying. I can't breathe. Keep\r\n"
"trying. I can't...";

const char * const rpg_key_opts[] = {"Continue", 0};

const char *rpg_cutters =
"You open the blades as wide as they'll go, but it's hard to get a decent grip.\r\n"
"Small snips then. Slow and steady wins the race. Which one's the jugular again?\r\n"
"Maybe--Yep. That?s the one. Oh... wow...";

const char * const rpg_cutters_opts[] = {"Continue", 0};

const char *rpg_hammer =
"Knocking out your teeth was the easy part. You flip it claw-side out and try\r\n"
"again. Ah. That?s much bett...";

const char * const rpg_hammer_opts[] = {"Continue", 0};

const char *rpg_rope =
"Good thing you have those extra ceiling hooks. Always be prepared. You string\r\n"
"the rope and pull it tight. Larry always laughed about it. Such a Boy Scout,\r\n"
"he'd say. You kick the toolbox out from under you. Who's laughing now, Larry?";

const char * const rpg_rope_opts[] = {"Continue", 0};


#endif	/* IMP_RPG_H */