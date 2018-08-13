
#ifndef ylabconfig_h
#define ylabconfig_h

#define MODULE_UPDATE_LOGIN "leheros"
#define MODULE_UPDATE_PASS "leheros1097"
#define HIDDEN_KEY "*****"
#define MODULE_AP_WPA ((const char *)"leheros1097")


#ifdef MCPOC_TEST

/* MATRIX DISPLAY MODULE*/
#define MATRIX_DISPLAY_NAME     ((const char *)"matrix-debug")
#define MATRIX_DISPLAY_MDNS     ((const char *)"matrixD")
#define MATRIX_DISPLAY_MDNS_AP  ((const char *)"matrixDAP")
#define MATRIX_DISPLAY_IP       192,168,0,101

/* VMC/METEO  MODULE*/
#define VMC_METEO_NAME        ((const char *)"vmc-meteo=debug")
#define VMC_METEO_MDNS        ((const char *)"vmc_meteoD")
#define VMC_METEO_MDNS_AP     ((const char *)"vmc_meteoDAP")
#define VMC_METEO_IP          192,168,0,111

/* CURRENT MODULE*/
#define CURRENT_NAME          ((const char *)"current-debug")
#define CURRENT_MDNS          ((const char *)"currentD")
#define CURRENT_MDNS_AP       ((const char *)"currentDAP")
#define CURRENT_IP            192,168,0,121
/* RONFLEUR MODULE*/
#define SNORER_NAME          ((const char *)"ronfleur-debug")
#define SNORER_MDNS          ((const char *)"ronfleurD")
#define SNORER_MDNS_AP       ((const char *)"ronfleurDAP")
#define SNORER_IP            192,168,0,131

/* CURRENT MODULE*/
#define CURRENT_GARAGE_NAME          ((const char *)"currentGar-debug")
#define CURRENT_GARAGE_MDNS          ((const char *)"currentGarD")
#define CURRENT_GARAGE_MDNS_AP       ((const char *)"currentGarDAP")
#define CURRENT_GARAGE_IP            192,168,0,141

/* VOICE MODULE*/
#define VOICE_NAME          ((const char *)"voice-debug")
#define VOICE_MDNS          ((const char *)"voiceD")
#define VOICE_MDNS_AP       ((const char *)"voiceDAP")
#define VOICE_IP            192,168,0,146

/* LAPORTE MODULE*/
#define LAPORTE_NAME          ((const char *)"laporte-debug")
#define LAPORTE_MDNS          ((const char *)"laporteD")
#define LAPORTE_MDNS_AP       ((const char *)"laporteDAP")
#define LAPORTE_IP            192,168,0,151/* LAPORTE MODULE*/

/* LAPORTE MODULE*/
#define LAPORTE_SONOR_NAME          ((const char *)"laporteSonor-debug")
#define LAPORTE_SONOR_MDNS          ((const char *)"laporteSonorD")
#define LAPORTE_SONOR_MDNS_AP       ((const char *)"laporteSonorDAP")
#define LAPORTE_SONOR_IP            192,168,0,156



#else

/* MATRIX DISPLAY MODULE*/
#define MATRIX_DISPLAY_NAME     ((const char *)"display-matrix")
#define MATRIX_DISPLAY_MDNS     ((const char *)"matrix")
#define MATRIX_DISPLAY_MDNS_AP  ((const char *)"matrixAP")
#define MATRIX_DISPLAY_IP       192,168,0,100
/* VMC/METEO  MODULE*/
#define VMC_METEO_NAME          ((const char *)"vmc-meteo")
#define VMC_METEO_MDNS_AP       ((const char *)"vmc_meteoAP")
#define VMC_METEO_MDNS          ((const char *)"vmc_meteo")
#define VMC_METEO_IP            192,168,0,110
/* CURRENT MODULE*/
#define CURRENT_NAME          ((const char *)"current")
#define CURRENT_MDNS          ((const char *)"current")
#define CURRENT_MDNS_AP       ((const char *)"currentAP")
#define CURRENT_IP            192,168,0,120

/* RONFLEUR MODULE*/
#define SNORER_NAME          ((const char *)"ronfleur")
#define SNORER_MDNS          ((const char *)"ronfleur")
#define SNORER_MDNS_AP       ((const char *)"ronfleurAP")
#define SNORER_IP            192,168,0,130
/* CURRENT MODULE*/
#define CURRENT_GARAGE_NAME          ((const char *)"currentGar")
#define CURRENT_GARAGE_MDNS          ((const char *)"currentGar")
#define CURRENT_GARAGE_MDNS_AP       ((const char *)"currentGarAP")
#define CURRENT_GARAGE_IP            192,168,0,140

/* VOICE MODULE*/
#define VOICE_NAME          ((const char *)"voice")
#define VOICE_MDNS          ((const char *)"voice")
#define VOICE_MDNS_AP       ((const char *)"voiceAP")
#define VOICE_IP            192,168,0,145

/* LAPORTE MODULE*/
#define LAPORTE_NAME          ((const char *)"laporte")
#define LAPORTE_MDNS          ((const char *)"laporte")
#define LAPORTE_MDNS_AP       ((const char *)"laporteAP")
#define LAPORTE_IP            192,168,0,150

/* LAPORTE MODULE*/
#define LAPORTE_SONOR_NAME          ((const char *)"laporteSonor-debug")
#define LAPORTE_SONOR_MDNS          ((const char *)"laporteSonorD")
#define LAPORTE_SONOR_MDNS_AP       ((const char *)"laporteSonorDAP")
#define LAPORTE_SONOR_IP            192,168,0,155


#endif

#define VMC_METEO_IP_PROD             "192.168.0.110"
#define CURRENT_IP_PROD               "192.168.0.120"
#define SNORER_IP_PROD                "192.168.0.130"
#define CURRENT_GARAGE_IP_PROD        "192.168.0.140"
#define VOICE_IP_PROD                 "192.168.0.145"
#define MATRIX_DISPLAY_IP_PROD        "192.168.0.100"
#define LAPORTE_SONOR_IP_PROD          "192,168,0,155"

#endif
