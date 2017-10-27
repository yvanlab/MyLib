
#ifndef ylabconfig_h
#define ylabconfig_h

#define MODULE_UPDATE_LOGIN "leheros"
#define MODULE_UPDATE_PASS "leheros1097"
#define HIDDEN_KEY "*****"

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

#endif

#define VMC_METEO_IP_PROD             "192.168.0.110"
#define CURRENT_IP_PROD               "192.168.0.120"
#define MATRIX_DISPLAY_IP_PROD        "192.168.0.100"

#endif
