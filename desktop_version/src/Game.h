#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <map>
#include <string>
#include <vector>

#include "Font.h"
#include "ScreenSettings.h"

/* FIXME: Can't forward declare this enum in C++, unfortunately.
 * In C, enum sizes are always the same, so you can forward declare them.
 * In C++ instead, enum sizes are based on how many enums there are.
 * You cannot specify the underlying type until C++11.
 * But bumping the standard opens up a can of worms. I'd rather just move to C. -Misa */
#include "Enums.h"

// Forward decl without including all of <tinyxml2.h>
namespace tinyxml2
{
    class XMLDocument;
    class XMLElement;
}

/* 40 chars (160 bytes) covers the entire screen, + 1 more for null terminator */
#define MENU_TEXT_BYTES 161

struct MenuOption
{
    char text[MENU_TEXT_BYTES];
    bool active;
    uint32_t print_flags;
};

//Menu IDs
namespace Menu
{
    enum MenuName
    {
        mainmenu,
        playerworlds,
        confirmshowlevelspath,
        showlevelspath,
        levellist,
        quickloadlevel,
        deletequicklevel,
        youwannaquit,
        errornostart,
        errorsavingsettings,
        errorloadinglevel,
        warninglevellist,
        graphicoptions,
        ed_settings,
        ed_desc,
        ed_music,
        ed_quit,
        ed_font,
        options,
        gameplayoptions,
        speedrunneroptions,
        setglitchrunner,
        advancedoptions,
        audiooptions,
        accessibility,
        controller,
        language,
        translator_main,
        translator_options,
        translator_options_limitscheck,
        translator_options_stats,
        translator_options_exploregame,
        translator_options_cutscenetest,
        translator_maintenance,
        translator_maintenance_sync,
        translator_error_setlangwritedir,
        cleardatamenu,
        clearcustomdatamenu,
        setinvincibility,
        setslowdown,
        unlockmenu,
        credits,
        credits2,
        credits25,
        credits3,
        credits4,
        credits5,
        credits6,
        credits_localisations_implementation,
        credits_localisations_translations,
        play,
        unlocktimetrial,
        unlocktimetrials,
        unlocknodeathmode,
        unlockintermission,
        unlockflipmode,
        newgamewarning,
        playmodes,
        intermissionmenu,
        playint1,
        playint2,
        continuemenu,
        startnodeathmode,
        gameover,
        gameover2,
        unlockmenutrials,
        timetrials,
        nodeathmodecomplete,
        nodeathmodecomplete2,
        timetrialcomplete,
        timetrialcomplete2,
        timetrialcomplete3,
        gamecompletecontinue
    };
}

enum SLIDERMODE
{
    SLIDER_NONE,
    SLIDER_MUSICVOLUME,
    SLIDER_SOUNDVOLUME
};

/* enums for swngame variable */
enum SWNMODE
{
    SWN_GRAVITRON,
    SWN_SUPERGRAVITRON,
    SWN_START_GRAVITRON_STEP_3,
    SWN_START_GRAVITRON_STEP_2,
    SWN_START_GRAVITRON_STEP_1,
    SWN_FINISH_GRAVITRON_STEP_1,
    SWN_START_SUPERGRAVITRON_STEP_1,
    SWN_START_SUPERGRAVITRON_STEP_2,
    SWN_FINISH_GRAVITRON_STEP_2,
    SWN_NONE
};

/* enums for unlock, unlocknotify arrays and unlocknum function */
enum
{
    Unlock_SPACESTATION1_COMPLETE = 0,
    Unlock_LABORATORY_COMPLETE = 1,
    Unlock_TOWER_COMPLETE = 2,
    Unlock_SPACESTATION2_COMPLETE = 3,
    Unlock_WARPZONE_COMPLETE = 4,
    UnlockTrophy_GAME_COMPLETE = 5,
    Unlock_INTERMISSION1_COMPLETE = 6,
    Unlock_INTERMISSION2_COMPLETE = 7,
    Unlock_SECRETLAB = 8,
    Unlock_TIMETRIAL_SPACESTATION1 = 9,
    Unlock_TIMETRIAL_LABORATORY = 10,
    Unlock_TIMETRIAL_TOWER = 11,
    Unlock_TIMETRIAL_SPACESTATION2 = 12,
    Unlock_TIMETRIAL_WARPZONE = 13,
    Unlock_TIMETRIAL_FINALLEVEL = 14,
    Unlock_INTERMISSION_UNUSED = 15,
    Unlock_INTERMISSION_REPLAYS = 16,
    Unlock_NODEATHMODE = 17,
    Unlock_FLIPMODE = 18,
    UnlockTrophy_FLIPMODE_COMPLETE = 19,
    UnlockTrophy_NODEATHMODE_COMPLETE = 20
};

/* enums for bestrank, bestlives, besttrinkets, besttimes, bestframes arrays
 * and timetriallevel */
enum
{
    TimeTrial_SPACESTATION1 = 0,
    TimeTrial_LABORATORY = 1,
    TimeTrial_TOWER = 2,
    TimeTrial_SPACESTATION2 = 3,
    TimeTrial_WARPZONE = 4,
    TimeTrial_FINALLEVEL = 5
};

struct MenuStackFrame
{
    int option;
    enum Menu::MenuName name;
};


class Game
{
    char magic[16];

public:
    
    //DDA RESEARCH: The DDA system
    
    //bool to stop research after completing Lab
    bool stopResearchGame = false;
    
    //DDA Death Location Storage
    struct DDADeathRecord {
        int x;
        int y;
        int room;                             //Room where player died
        int deathNumber;                      //Which death this was (1st, 2nd, etc.)
        int timestamp;                        //Game time in seconds when death occurred
    };

    //Per-room DDA tracking that persist after room changes
    struct DDARoomState {
        int deaths;                           //Total deaths in this room
        int timeSpentSeconds;                 //Accumulated time in this room
        bool struggled;                       //Has player struggled in this room?
        bool completed;
    };

    //DDA System Variables
    bool ddaEnabled;                          //Enable/disable entire DDA system
    bool ddaFirstDDARoom;                     //True until first DDA room is completed

    //Core difficulty
    int ddaDifficulty;                        //1-7, will start at 4
    int ddaCurrentRoom;                       //Current room player is in (0-63)
    int ddaFurthestRoomReached;               //Furthest room player has entered

    //Room tracking
    int ddaDeathsInRoom;                      //Deaths in current room
    int ddaRoomStartTime;                     //Timestamp when room was entered (in total seconds)
    int ddaSameSpotDeaths;                    //Count of deaths in same spot, updated on death, for same death location comparison
    bool ddaStruggledThisRoom;                //Is player currently struggling?
    int ddaSuccessStreak;
    bool ddaAssumedSuccess;                   //Did we pre-increase difficulty for this room?
    int ddaPreAssumeDifficulty;               //Difficulty before assuming (for telemetry)

    //Death location tracking (store last 10 deaths)
    static const int DDA_MAX_DEATH_RECORDS = 10;
    DDADeathRecord ddaDeathRecords[DDA_MAX_DEATH_RECORDS];
    int ddaDeathRecordCount;                     //How many records currently stored

    //Checkpoint spawning
    //Index corresponds to room number, true = extra checkpoint spawned
    static const int DDA_MAX_ROOMS = 64;
    bool ddaAddCheckpoint1[DDA_MAX_ROOMS];  //First checkpoint in room
    bool ddaAddCheckpoint2[DDA_MAX_ROOMS];  //Second checkpoint in room (if there is one)

    //Rooms configuration (set these up during initialization)
    int ddaDeathThreshold[DDA_MAX_ROOMS];     // Deaths before considered "struggling"
    int ddaShortTimeThreshold[DDA_MAX_ROOMS];      //Seconds before considered "struggling lightly"
    int ddaLongTimeThreshold[DDA_MAX_ROOMS];      //Seconds before considered "struggling heavily"

    bool ddaRoomHasDDA[DDA_MAX_ROOMS];        //false for tutorial rooms and final rooms
    int ddaRoomLevel[DDA_MAX_ROOMS];          //0 = tutorial/end of space station/lab, 1 = Space Station, 2 = Laboratory
    DDARoomState ddaRoomState[DDA_MAX_ROOMS]; //Room DDA tracking

    //DDA System Functions
    void ddaInit();
    void ddaReset();

    void ddaUpdate(); //Update DDA
    bool ddaRoomCheckpointsLocked[DDA_MAX_ROOMS];   //Once checkpoints set for a room, don't change

    void ddaOnPlayerDeath();                        //Called when player dies
    void ddaOnRoomEnter(int room);                  //Called when entering new room
    void ddaOnRoomComplete(int room);               //Called when completing a room
    void ddaEvaluateAndAdjust();                    //Evaluate struggle and adjust difficulty
    void ddaCheckStruggle();                        //Check for struggling
    void ddaAddCheckpointsForRoom(int room);        //Determine checkpoints for a room
    void ddaUpdateCheckpoints();                    //Update checkpoints

    int ddaGetTotalGameSeconds();                   //Get current game time in seconds
    int ddaGetRoomIndex(const std::string& name);   //Map room name to index (0-63)
    //DDA RESEARCH - END

    //=======================================================================

    //DDA RESEARCH: Telemetry
    struct TelemetryRoomData {
        int timeSpentSeconds;                    //Total time spent in this room
        int difficultyOnEntry;                   //Difficulty level when first entering
        int totalDeaths;                         //Total deaths in this room
        DDADeathRecord deaths[100];              //Reuse DDADeathRecord, with up to 100 deaths per room
        int deathCount;                          //Actual number of deaths recorded
        bool visited;                            //Has player visited this room?
    };

    TelemetryRoomData telemetryRooms[DDA_MAX_ROOMS];  //Data for each of 64 rooms
    int telemetryCheckpointsActivated;                //Count of unique checkpoint activations

    //Difficulty change tracking for telemetry
    struct TelemetryDifficultyChange {
        int room;                    //Room where change occurred
        int oldDifficulty;
        int newDifficulty;
        int timestamp;               //Game seconds when change occurred
        bool isDecrease;             //true = decrease (struggle), false = increase (success)
        int struggleCondition;       //Only for decreases: 1=longTime, 2=deaths+shortTime, 3=sameSpot+shortTime, 4=sameSpot+deaths
    };

    static const int TELEMETRY_MAX_DIFFICULTY_CHANGES = 50;
    TelemetryDifficultyChange telemetryDifficultyChanges[TELEMETRY_MAX_DIFFICULTY_CHANGES];
    int telemetryDifficultyChangeCount;

    //Tracking up to 200 checkpoints total
    int telemetryActivatedCheckpointIDs[200];         //Store the checkpoint ID values
    int telemetryActivatedCheckpointCount;            //How many unique checkpoints activated
    int telemetryTotalKeyPresses;                     //Total key presses during gameplay
    int telemetryGameStartSeconds;                    //When gameplay started for key presses per minute (KPM) calculation

    //Key state tracking for detecting key-down events
    bool telemetryKeyWasDown_left;
    bool telemetryKeyWasDown_right;
    bool telemetryKeyWasDown_action;

    //Key press tracking per minute
    static const int TELEMETRY_MAX_MINUTES = 60;      //Up to 60 minutes of gameplay, which is very unlikely to ever be reached
    int telemetryKeyPressesPerMinute[TELEMETRY_MAX_MINUTES];

    //Telemetry functions
    void telemetryInit();
    void telemetryOnRoomEnter(int room);              //Called when entering a room (first time only records difficulty)
    void telemetryOnRoomExit(int room);               //Called when leaving a room (records time spent)
    void telemetryOnDeath(int room, int x, int y);    //Called on each death
    void telemetryOnCheckpointActivated(int checkpointID);  //Called when checkpoint is activated
    void telemetryOnKeyPress();                       //Called on each key press (up->down transition)
    void telemetryUpdateKeyTracking();                //Called each frame to detect key presses
    void telemetryWriteLog();                         //Write all data to file
    std::string telemetryGetRoomName(int index);      //Get room name from index

    //Platform-specific telemetry export
    void telemetryWriteLocalFile(int totalGameSeconds, float kpm);  //Desktop: write to file
    #ifdef __EMSCRIPTEN__
    void telemetrySendToGoogleSheets(int totalGameSeconds, float kpm);  //Web: send to Google Sheets
    #endif

    //DDA TELEMETRY - END

    
    void init(void);
    void setdefaultcontrollerbuttons(void);


    int crewrescued(void);

    std::string unrescued(void);

    void resetgameclock(void);

    bool customsavequick(const std::string& savfile);
    bool savequick(void);

    void gameclock(void);

    std::string giventimestring(int hrs, int min, int sec);

    std::string  timestring(void);

    std::string resulttimestring(void);

    std::string timetstring(int t);

    void timestringcenti(char* buffer, size_t buffer_size);

    void returnmenu(void);
    void returntomenu(enum Menu::MenuName t);
    void  createmenu(enum Menu::MenuName t, bool samemenu = false);
    bool can_unlock_ndm(void);
    void unlock_ndm(void);

    void lifesequence(void);

    void gethardestroom(void);

    void levelcomplete_textbox(void);
    void crewmate_textbox(const int color);
    void remaining_textbox(void);
    void actionprompt_textbox(void);
    void show_save_fail(void);
    void checkpoint_save(void);
    void savetele_textbox(void);

    void setstate(int gamestate);

    void incstate(void);

    void setstatedelay(int delay);

    void lockstate(void);

    void unlockstate(void);

    void updatestate(void);

    void unlocknum(int t);

    void loadstats(struct ScreenSettings* screen_settings);

    bool savestats(const struct ScreenSettings* screen_settings, bool sync = true);
    bool savestats(bool sync = true);

    void deletestats(void);

    void deserializesettings(tinyxml2::XMLElement* dataNode, struct ScreenSettings* screen_settings);

    void serializesettings(tinyxml2::XMLElement* dataNode, const struct ScreenSettings* screen_settings);

    void loadsettings(struct ScreenSettings* screen_settings);

    bool savesettings(const struct ScreenSettings* screen_settings);
    bool savesettings(void);

    bool savestatsandsettings(void);

    void savestatsandsettings_menu(void);

    void deletesettings(void);

    void deletequick(void);

    bool savetele(void);

    void loadtele(void);

    void deletetele(void);

    void customstart(void);

    void start(void);

    void startspecial(int t);

    void starttrial(int t);

    void swnpenalty(void);

    void deathsequence(void);

    void customloadquick(const std::string& savfile);
    void loadquick(void);

    void customdeletequick(const std::string& file);

    void loadsummary(void);

    static const int numcrew = 6;

    struct Summary
    {
        bool exists;
        int seconds;
        int minutes;
        int hours;
        int saverx;
        int savery;
        int trinkets;
        bool crewstats[numcrew];
    };

    struct Summary last_telesave, last_quicksave;
    bool save_exists(void);

    void readmaingamesave(const char* savename, tinyxml2::XMLDocument& doc);
    struct Summary writemaingamesave(tinyxml2::XMLDocument& doc);

    void initteleportermode(void);

    const char* saveFilePath;


    int roomx, roomy;
    int prevroomx, prevroomy;

    int savex, savey, saverx, savery;
    int savegc, savedir;
    int savecolour;

    //Added for port
    int edsavex, edsavey, edsaverx, edsavery;
    int edsavegc, edsavedir;

    //State logic stuff
    int state, statedelay;

    bool glitchrunkludge;

    enum GameGamestate gamestate;
    enum GameGamestate prevgamestate; //only used sometimes
    bool hascontrol, jumpheld;
    int jumppressed;
    int gravitycontrol;
    bool isingamecompletescreen(void);

    bool muted;
    int mutebutton;
    bool musicmuted;
    int musicmutebutton;

    int tapleft, tapright;

    //Menu interaction stuff
    void mapmenuchange(const enum GameGamestate newgamestate, const bool user_initiated);
    bool mapheld;
    int menupage;
    int lastsaved;
    int deathcounts;

    int framecounter;
    bool seed_use_sdl_getticks;
    bool editor_disabled;
    int frames, seconds, minutes, hours;
    bool gamesaved;
    bool gamesavefailed;
    std::string savetime;
    int saveframes, saveseconds;
    int savetrinkets;
    bool startscript;
    std::string newscript;
    bool checkpoint_saving;

    bool menustart;

    //Teleporting
    bool teleport_to_new_area;
    int teleport_to_x, teleport_to_y;
    std::string teleportscript;
    bool useteleporter;
    int teleport_to_teleporter;

    //Main Menu Variables
    std::vector<MenuOption> menuoptions;
    int currentmenuoption ;
    bool menutestmode;
    enum Menu::MenuName currentmenuname;
    enum Menu::MenuName kludge_ingametemp;
    enum SLIDERMODE slidermode;
    int current_credits_list_index;
    int translator_credits_pagenum;
    int menuxoff, menuyoff;
    int menuspacing;
    std::vector<MenuStackFrame> menustack;

    void inline option(const char* text, bool active = true, uint32_t print_flags = PR_RTL_XFLIP)
    {
        MenuOption menuoption;
        SDL_strlcpy(menuoption.text, text, sizeof(menuoption.text));
        menuoption.active = active;
        menuoption.print_flags = print_flags;
        menuoptions.push_back(menuoption);
    }

    int menucountdown;
    enum Menu::MenuName menudest;

    int creditposx, creditposy, creditposdelay;
    int oldcreditposx;

    SDL_GameControllerButton gpmenu_lastbutton;
    bool gpmenu_confirming;
    bool gpmenu_showremove;

    bool silence_settings_error;


    //Sine Wave Ninja Minigame
    bool swnmode;
    enum SWNMODE swngame;
    int swnstate, swnstate2, swnstate3, swnstate4, swndelay, swndeaths;
    int swntimer, swncolstate, swncoldelay;
    int  swnrecord, swnbestrank, swnrank, swnmessage;

    //SuperCrewMate Stuff
    bool supercrewmate, scmhurt;
    int scmprogress;

    //Accessibility Options
    bool  colourblindmode;
    bool noflashingmode;
    int slowdown;
    int get_timestep(void);
    bool physics_frozen(void);

    bool nodeathmode;
    int gameoverdelay;
    bool nocutscenes;
    int ndmresultcrewrescued;
    int ndmresulttrinkets;
    std::string ndmresulthardestroom;
    int ndmresulthardestroom_x;
    int ndmresulthardestroom_y;
    bool ndmresulthardestroom_specialname;
    void copyndmresults(void);
    bool nodeatheligible;
    void invalidate_ndm_trophy(void);

    //Time Trials
    bool intimetrial, timetrialparlost;
    int timetrialcountdown, timetrialshinytarget, timetriallevel;
    int timetrialpar, timetrialresulttime, timetrialresultframes, timetrialrank;
    bool timetrialcheater;
    int timetrialresultshinytarget, timetrialresulttrinkets, timetrialresultpar;
    int timetrialresultdeaths;

    bool start_translator_exploring;
    bool translator_exploring;
    bool translator_exploring_allowtele;
    bool translator_cutscene_test;

    size_t cutscenetest_menu_page;
    std::string cutscenetest_menu_play_id;

    int creditposition;
    int oldcreditposition;
    bool insecretlab;

    bool inintermission;

    bool crewstats[numcrew];
    bool ndmresultcrewstats[numcrew];

    bool alarmon;
    int alarmdelay;
    bool blackout;

    static const int numunlock = 25;
    bool unlock[numunlock];
    bool unlocknotify[numunlock];
    bool anything_unlocked(void);
    int stat_trinkets;
    int bestgamedeaths;


    static const int numtrials = 6;
    int besttimes[numtrials];
    int bestframes[numtrials];
    int besttrinkets[numtrials];
    int bestlives[numtrials];
    int bestrank[numtrials];

    int screenshake, flashlight;
    bool advancetext, pausescript;

    int deathseq, lifeseq;

    int trinkets(void);
    int crewmates(void);
    int savepoint, teleportxpos;
    bool teleport;
    int edteleportent;
    bool completestop;

    float inertia;

    int companion;
    SDL_Rect teleblock;
    bool activetele;
    int readytotele;
    int oldreadytotele;
    int activity_r, activity_g, activity_b, activity_y;
    std::string activity_lastprompt;
    bool activity_gettext;

    bool backgroundtext;

    int activeactivity, act_fade;
    int prev_act_fade;

    bool press_left, press_right, press_action, press_map, press_interact;
    bool interactheld;
    bool separate_interact;

    //Some stats:
    int totalflips;
    std::string hardestroom; // don't change to C string unless you wanna handle when this string is loaded from the XML
    int hardestroomdeaths, currentroomdeaths;
    int hardestroom_x, hardestroom_y;
    bool hardestroom_specialname;
    bool hardestroom_finalstretch;


    bool quickrestartkludge;

    //Custom stuff
    std::string customscript[50];
    int customcol;
    int levelpage;
    int playcustomlevel;
    std::string customleveltitle;
    std::string customlevelfilename;

    void clearcustomlevelstats(void);
    void loadcustomlevelstats(void);
    void savecustomlevelstats(void);
    void updatecustomlevelstats(std::string clevel, int cscore);
    void deletecustomlevelstats(void);

    // name -> score. 0 - not played, 1 - finished, 2 - all trinkets, 3 - finished, all trinkets
    std::map<std::string, int> customlevelstats;


    std::vector<SDL_GameControllerButton> controllerButton_map;
    std::vector<SDL_GameControllerButton> controllerButton_flip;
    std::vector<SDL_GameControllerButton> controllerButton_esc;
    std::vector<SDL_GameControllerButton> controllerButton_restart;
    std::vector<SDL_GameControllerButton> controllerButton_interact;

    bool skipfakeload;
    bool ghostsenabled;

    bool cliplaytest;
    int playx;
    int playy;
    int playrx;
    int playry;
    int playgc;
    int playmusic;
    std::string playassets;

    void quittomenu(void);
    void returntolab(void);
    bool fadetomenu;
    int fadetomenudelay;
    bool fadetolab;
    int fadetolabdelay;

    void returntoeditor(void);

    bool inline inspecial(void)
    {
        return inintermission || insecretlab || intimetrial || nodeathmode || translator_exploring;
    }

    bool incompetitive(void);

    bool nocompetitive(void);
    bool nocompetitive_unless_translator(void);

    void sabotage_time_trial(void);

    bool over30mode;
    bool showingametimer;

    bool ingame_titlemode;
    bool ingame_editormode;

    void returntoingame(void);
    void unlockAchievement(const char *name);

    bool disablepause;
    bool disableaudiopause;
    bool disabletemporaryaudiopause;
    bool inputdelay;

    bool statelocked;

    int old_skip_message_timer;
    int skip_message_timer;

    int old_mode_indicator_timer;
    int mode_indicator_timer;

    int old_screenshot_border_timer;
    int screenshot_border_timer;
    bool screenshot_saved_success;
};

#ifndef GAME_DEFINITION
extern Game game;
#endif

#endif /* GAME_H */
