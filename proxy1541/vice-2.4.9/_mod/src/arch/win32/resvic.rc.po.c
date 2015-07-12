
#include "vice.h"

#include "res.h"
#include "rescommon.h"

#ifndef WINDRES_CP_IGNORE
#pragma code_page(28591)
#endif


IDD_VIC_DIALOG DIALOG DISCARDABLE 0, 0, 145, 160
BEGIN
    GROUPBOX        "", IDC_VIC_BORDERSGROUP,
                    10, 5, 125, 70
    AUTORADIOBUTTON "", IDC_TOGGLE_VIC_NORMALBORDERS,
                    15, 15, 115, 10, BS_AUTORADIOBUTTON | WS_GROUP | WS_TABSTOP
    AUTORADIOBUTTON "", IDC_TOGGLE_VIC_FULLBORDERS,
                    15, 30, 115, 10, BS_AUTORADIOBUTTON | WS_TABSTOP
    AUTORADIOBUTTON "", IDC_TOGGLE_VIC_DEBUGBORDERS,
                    15, 45, 115, 10, BS_AUTORADIOBUTTON | WS_TABSTOP
    AUTORADIOBUTTON "", IDC_TOGGLE_VIC_NOBORDERS,
                    15, 60, 115, 10, BS_AUTORADIOBUTTON | WS_TABSTOP

    DEFPUSHBUTTON   "", IDOK, 15, 140, 50, 14, WS_TABSTOP
    PUSHBUTTON      "", IDCANCEL, 70, 140, 50, 14, WS_TABSTOP
END



STRINGTABLE
BEGIN
    IDS_VIC_CAPTION       N_("VIC settings")
    IDS_VIC_BORDERSGROUP  N_("Border mode")
    IDS_VIC_NORMALBORDERS N_("Normal borders")
    IDS_VIC_FULLBORDERS   N_("Full borders")
    IDS_VIC_DEBUGBORDERS  N_("Debug borders")
    IDS_VIC_NOBORDERS     N_("No borders")
END



STRINGTABLE
LANGUAGE LANG_DANISH, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "VIC-indstillinger"
    IDS_VIC_BORDERSGROUP  "Ramme-tilstand"
    IDS_VIC_NORMALBORDERS "Normal ramme"
    IDS_VIC_FULLBORDERS   "Fuld ramme"
    IDS_VIC_DEBUGBORDERS  "Debug-ramme"
    IDS_VIC_NOBORDERS     "Ingen rammer"
END



STRINGTABLE
LANGUAGE LANG_GERMAN, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "VIC Einstellungen"
    IDS_VIC_BORDERSGROUP  "Rahmen Modus"
    IDS_VIC_NORMALBORDERS "Normaler Rahmen"
    IDS_VIC_FULLBORDERS   "Voller Rahmen"
    IDS_VIC_DEBUGBORDERS  "Rahmen debuggen"
    IDS_VIC_NOBORDERS     "Kein Rahmen"
END



STRINGTABLE
LANGUAGE LANG_SPANISH, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "Ajustes VIC"
    IDS_VIC_BORDERSGROUP  "Modo del borde"
    IDS_VIC_NORMALBORDERS "Bordes normales"
    IDS_VIC_FULLBORDERS   "Bordes completos"
    IDS_VIC_DEBUGBORDERS  "Bordes de prueba"
    IDS_VIC_NOBORDERS     "Sin bordes"
END



STRINGTABLE
LANGUAGE LANG_FRENCH, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "Paramètres VIC"
    IDS_VIC_BORDERSGROUP  "Mode Bordure"
    IDS_VIC_NORMALBORDERS "Bordures normales"
    IDS_VIC_FULLBORDERS   "Bordures complètes"
    IDS_VIC_DEBUGBORDERS  "Bordures de déboguage"
    IDS_VIC_NOBORDERS     "Pas de bordures"
END



#ifndef WINDRES_CP_IGNORE
#pragma code_page(28592)
#endif
STRINGTABLE
LANGUAGE LANG_HUNGARIAN, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "VIC beállításai"
    IDS_VIC_BORDERSGROUP  "Keret mód"
    IDS_VIC_NORMALBORDERS "Normal borders"
    IDS_VIC_FULLBORDERS   "Full borders"
    IDS_VIC_DEBUGBORDERS  "Debug borders"
    IDS_VIC_NOBORDERS     "No borders"
END
#ifndef WINDRES_CP_IGNORE
#pragma code_page(28591)
#endif



STRINGTABLE
LANGUAGE LANG_ITALIAN, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "Impostazioni VIC"
    IDS_VIC_BORDERSGROUP  "Modalità del bordo"
    IDS_VIC_NORMALBORDERS "Bordi normali"
    IDS_VIC_FULLBORDERS   "Bordi pieni"
    IDS_VIC_DEBUGBORDERS  "Bordi in debug"
    IDS_VIC_NOBORDERS     "Senza bordi"
END



#ifndef WINDRES_CP_IGNORE
#pragma code_page(949)
#endif
STRINGTABLE
LANGUAGE LANG_KOREAN, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "VIC ¼ÂÆÃ"
    IDS_VIC_BORDERSGROUP  "º¸´õ ¸ðµå"
    IDS_VIC_NORMALBORDERS "Normal borders"
    IDS_VIC_FULLBORDERS   "Full borders"
    IDS_VIC_DEBUGBORDERS  "Debug borders"
    IDS_VIC_NOBORDERS     "No borders"
END
#ifndef WINDRES_CP_IGNORE
#pragma code_page(28591)
#endif



STRINGTABLE
LANGUAGE LANG_DUTCH, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "VIC instellingen"
    IDS_VIC_BORDERSGROUP  "Bordermodus"
    IDS_VIC_NORMALBORDERS "Normale borders"
    IDS_VIC_FULLBORDERS   "Volle borders"
    IDS_VIC_DEBUGBORDERS  "Debug borders"
    IDS_VIC_NOBORDERS     "Geen borders"
END



#ifndef WINDRES_CP_IGNORE
#pragma code_page(28592)
#endif
STRINGTABLE
LANGUAGE LANG_POLISH, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "Ustawienia VIC"
    IDS_VIC_BORDERSGROUP  "Tryb ramki"
    IDS_VIC_NORMALBORDERS "Zwyk³a ramka"
    IDS_VIC_FULLBORDERS   "Pe³na ramka"
    IDS_VIC_DEBUGBORDERS  "Ramka debugowania"
    IDS_VIC_NOBORDERS     "Bez ramki"
END
#ifndef WINDRES_CP_IGNORE
#pragma code_page(28591)
#endif



#ifndef WINDRES_CP_IGNORE
#pragma code_page(28595)
#endif
STRINGTABLE
LANGUAGE LANG_RUSSIAN, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "VIC settings"
    IDS_VIC_BORDERSGROUP  "Border mode"
    IDS_VIC_NORMALBORDERS "Normal borders"
    IDS_VIC_FULLBORDERS   "Full borders"
    IDS_VIC_DEBUGBORDERS  "Debug borders"
    IDS_VIC_NOBORDERS     "No borders"
END
#ifndef WINDRES_CP_IGNORE
#pragma code_page(28591)
#endif



STRINGTABLE
LANGUAGE LANG_SWEDISH, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "VIC-inställningar"
    IDS_VIC_BORDERSGROUP  "Ramläge"
    IDS_VIC_NORMALBORDERS "Vanliga ramar"
    IDS_VIC_FULLBORDERS   "Fullständinga ramar"
    IDS_VIC_DEBUGBORDERS  "Felsökningsramar"
    IDS_VIC_NOBORDERS     "Inga ramar"
END



#ifndef WINDRES_CP_IGNORE
#pragma code_page(28599)
#endif
STRINGTABLE
LANGUAGE LANG_TURKISH, SUBLANG_NEUTRAL
BEGIN
    IDS_VIC_CAPTION       "VIC ayarlarý"
    IDS_VIC_BORDERSGROUP  "Çerçeve modu"
    IDS_VIC_NORMALBORDERS "Normal çerçeve"
    IDS_VIC_FULLBORDERS   "Tam çerçeve"
    IDS_VIC_DEBUGBORDERS  "Hata ayýklama çerçevesi"
    IDS_VIC_NOBORDERS     "Çerçeve yok"
END
#ifndef WINDRES_CP_IGNORE
#pragma code_page(28591)
#endif


