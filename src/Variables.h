#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

typedef void *VAR;

//-----------------------------MEMORY FREE--------------------------------
//                 $~ Free memory of Variables struct ~$
//------------------------------Arguments---------------------------------
//        VAR <--  hides internal declaration of Variables struct
//                    var <-- reference to Variables
void memoryFree(VAR var);
//------------------------------------------------------------------------

//-----------------------------CREATE VAR---------------------------------
//               $~ Allocate memory to Variables struct ~$
//--------------------------------Return----------------------------------
//  Returns reference pointer to an empty Variables struct block of memory
VAR createVAR();
//------------------------------------------------------------------------

//----------------------------GET FUNCTIONS---------------------------
//            $~ Gets a copy of Variables struct content ~$
//-------------------------------Return-------------------------------
//         Returns a copy of value stored in Variables struct     
//-----------------------------Arguments------------------------------
//      VAR <--  hides internal declaration of struct Variables
//                    var <-- reference to Variables
char *getARG_PathBED(VAR var);
char *getARG_PathBED_qry(VAR var);
char *getARG_PathBED_geo(VAR var);
char *getARG_PathBSD(VAR var);
char *getARG_geo(VAR var);
char *getARG_qry(VAR var);
char *getARG_Log(VAR var);
char *getARG_title(VAR var);
char *getBED_DataCollectPath(VAR var);
char *getBED_tempLog(VAR var);
char *getBSD_LogGeo(VAR var);
char *getBSD_LogSvg(VAR var);
char *getArqConsTXT(VAR var);
char *getArqConsSVG(VAR var);
char *getCC(VAR var);
char *getCP(VAR var);
long int getDEF_SIZE(VAR var);
int getVisits(VAR var);
int getColor(VAR var);
//------------------------------------------------------------------------

/**/
#endif