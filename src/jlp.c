#include <string.h>
#include <curl/curl.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "jlp/jlp.h"

struct JLP_Context {
    char *appid;
    char *sentence;
    JLP_Bool results_ma;
    JLP_Bool results_uniq;
    JLP_Bool response_surface;
    JLP_Bool response_reading;
    JLP_Bool response_pos;
    JLP_Bool response_baseform;
    JLP_Bool response_feature;
    char *filter;
    char *ma_filter;
    char *uniq_response;
    char *uniq_filter;
    char *uniq_by_baseform;
};
struct JLP_Result {
    xmlDoc *dom;
};

static const char *JLP_REQUEST_URL = "http://jlp.yahooapis.jp/MAService/V1/parse?";

JLP_Context *JLP_Context_Create(char *appid) {
    JLP_Error error = JLP_ERROR_NONE;
    JLP_Context *tmp_ctx;
    {/* init context */
        if(!(tmp_ctx = JLP_Calloc(1, sizeof(JLP_Context)))) {
            error = JLP_ERROR_MEMORY;
            goto ERROR;
        }
    }
    {/* set appid */
        if(!(tmp_ctx -> appid = JLP_Malloc(strlen(appid) + 1))) {
            error = JLP_ERROR_MEMORY;
            goto ERROR;
        }
        strcpy(tmp_ctx -> appid, appid);
    }

    {/* init results value */
        tmp_ctx -> results_ma = JLP_TRUE;
    }
    {/* init response value */
        tmp_ctx -> response_surface = JLP_TRUE;
        tmp_ctx -> response_reading = JLP_TRUE;
        tmp_ctx -> response_pos = JLP_TRUE;
    }
    return tmp_ctx;
ERROR:
    JLP_Context_Dispose(tmp_ctx);
    return NULL;
}
void JLP_Context_Dispose(JLP_Context *ctx) {
    if(ctx) {
        JLP_Free(ctx -> appid);
        JLP_Free(ctx -> filter);
        JLP_Free(ctx -> ma_filter);
        JLP_Free(ctx -> uniq_response);
        JLP_Free(ctx -> uniq_filter);
        JLP_Free(ctx -> uniq_by_baseform);
        JLP_Free(ctx);
    }
}
void JLP_Context_SetSentence(JLP_Context *ctx, char *sentence) {
    ctx -> sentence = sentence;
}
void JLP_Context_SetResults(JLP_Context *ctx, JLP_Bool ma, JLP_Bool uniq) {
    ctx -> results_ma = ma;
    ctx -> results_uniq = uniq;
}
void JLP_Context_SetResponse(JLP_Context *ctx, JLP_Bool surface,
        JLP_Bool reading, JLP_Bool pos, JLP_Bool baseform, JLP_Bool feature) {
    ctx -> response_surface = surface;
    ctx -> response_reading = reading;
    ctx -> response_pos = pos;
    ctx -> response_baseform = baseform;
    ctx -> response_feature = feature;
}
JLP_Error JLP_Context_SetFilter(JLP_Context *ctx, char *filter) {
    JLP_Error error = JLP_ERROR_NONE;

    if(!(ctx -> filter = JLP_Malloc(strlen(filter) + 1))) {
        error = JLP_ERROR_MEMORY;
        goto ERROR;
    }
    strcpy(ctx -> filter, filter);
    return error;
ERROR:
    return error;
}
JLP_Error JLP_Context_SetMaFilter(JLP_Context *ctx, char *ma_filter) {
    JLP_Error error = JLP_ERROR_NONE;

    if(!(ctx -> ma_filter = JLP_Malloc(strlen(ma_filter) + 1))) {
        error = JLP_ERROR_MEMORY;
        goto ERROR;
    }
    strcpy(ctx -> ma_filter, ma_filter);
    return error;
ERROR:
    return error;
}
JLP_Error JLP_Context_SetUniqResponse(JLP_Context *ctx, char *uniq_response) {
    JLP_Error error = JLP_ERROR_NONE;

    if(!(ctx -> uniq_response = JLP_Malloc(strlen(uniq_response) + 1))) {
        error = JLP_ERROR_MEMORY;
        goto ERROR;
    }
    strcpy(ctx -> uniq_response, uniq_response);
    return error;
ERROR:
    return error;
}
JLP_Error JLP_Context_SetUniqFilter(JLP_Context *ctx, char *uniq_filter) {
    JLP_Error error = JLP_ERROR_NONE;

    if(!(ctx -> uniq_filter = JLP_Malloc(strlen(uniq_filter) + 1))) {
        error = JLP_ERROR_MEMORY;
        goto ERROR;
    }
    strcpy(ctx -> uniq_filter, uniq_filter);
    return error;
ERROR:
    return error;
}
JLP_Error JLP_Context_SetUniqByBaseform(JLP_Context *ctx, char *uniq_by_baseform) {
    JLP_Error error = JLP_ERROR_NONE;

    if(!(ctx -> uniq_by_baseform = JLP_Malloc(strlen(uniq_by_baseform) + 1))) {
        error = JLP_ERROR_MEMORY;
        goto ERROR;
    }
    strcpy(ctx -> uniq_by_baseform, uniq_by_baseform);
    return error;
ERROR:
    return error;
}
static JLP_Error jlp_requst_url_create(JLP_Context *ctx, char **url) {
    JLP_Error error = JLP_ERROR_NONE;
    char *tmp_url;
    char *tmp_value;

    if(!(tmp_url = JLP_Calloc(1, strlen(JLP_REQUEST_URL) + 1))) {
        error = JLP_ERROR_MEMORY;
        goto ERROR;
    }
    strcpy(tmp_url, JLP_REQUEST_URL);

    /* appid value */
    if(ctx -> appid) {
        tmp_value = "appid=";
        if(!(tmp_url = JLP_Realloc(tmp_url, strlen(tmp_url) + strlen(tmp_value) + strlen(ctx -> appid) + 1))) {
            error = JLP_ERROR_MEMORY;
            goto ERROR;
        }
        strcat(tmp_url, tmp_value);
        strcat(tmp_url, ctx -> appid);
    } else {
        error = JLP_ERROR_PARAMETER;
        goto ERROR;
    }

    /* sentence */
    if(ctx -> sentence) {
        tmp_value = "&sentence=";
        if(!(tmp_url = JLP_Realloc(tmp_url, strlen(tmp_url) + strlen(tmp_value) + strlen(ctx -> sentence) + 1))) {
            error = JLP_ERROR_MEMORY;
            goto ERROR;
        }
        strcat(tmp_url, tmp_value);
        strcat(tmp_url, ctx -> sentence);
    } else {
        error = JLP_ERROR_PARAMETER;
        goto ERROR;
    }

    /* results value */
    if(!ctx -> results_ma && !ctx -> results_uniq) {
        error = JLP_ERROR_PARAMETER;
        goto ERROR;
    }
    if(ctx -> results_ma) {
        tmp_value = "&results=ma";
        if(!(tmp_url = JLP_Realloc(tmp_url, strlen(tmp_url) + strlen(tmp_value) + 1))) {
            error = JLP_ERROR_MEMORY;
            goto ERROR;
        }
        strcat(tmp_url, tmp_value);
    }
    if(ctx -> results_uniq) {
        if(ctx -> results_ma) {
            tmp_value = ",uniq";
        } else {
            tmp_value = "&results=uniq";
        }

        if(!(tmp_url = JLP_Realloc(tmp_url, strlen(tmp_url) + strlen(tmp_value) + 1))) {
            error = JLP_ERROR_MEMORY;
            goto ERROR;
        }
        strcat(tmp_url, tmp_value);
    }

    /* filter */
    if(ctx -> filter) {
        tmp_value = "&filter=";
        if(!(tmp_url = JLP_Realloc(tmp_url, strlen(tmp_url) + strlen(tmp_value) +
                strlen(ctx -> filter) + 1))) {
            error = JLP_ERROR_MEMORY;
                    goto ERROR;
        }
        strcat(tmp_url, tmp_value);
        strcat(tmp_url, ctx -> filter);
    }


    *url = tmp_url;
    return error;
ERROR:
    JLP_Free(tmp_url);
    return error;
}

typedef struct {
    char *data;
    size_t dataLen;
    size_t dataMaxLen;
} JLP_Server_Response;

static size_t write_data( void *buffer, size_t size, size_t nmemb, void *userp ) {
  int segsize = size * nmemb;
  JLP_Server_Response *res = (JLP_Server_Response *)userp;

  /* Copy the data from the curl buffer into our buffer */
  if(res -> dataMaxLen - res -> dataLen < segsize) {
      res -> data = JLP_Realloc(res -> data, res -> dataMaxLen + segsize + JLP_DEFAULT_BUFSIZE);
      res -> dataMaxLen += segsize + JLP_DEFAULT_BUFSIZE;
  }
  memcpy(res->data + res->dataLen, buffer, segsize);

  /* Update the write index */
  res->dataLen += segsize;

  /* Return the number of bytes received, indicating to curl that all is okay */
  return segsize;
}

static JLP_Error jlp_http_get(char *url, char **data) {
    JLP_Error error = JLP_ERROR_NONE;
    CURL *curl;
    CURLcode status;
    JLP_Server_Response res;

    {/* init res */
        memset(&res, 0, sizeof(JLP_Server_Response));
        if(!(res.data = JLP_Malloc(JLP_DEFAULT_BUFSIZE * sizeof(char)))) {
            error = JLP_ERROR_MEMORY;
            goto ERROR;
        }
        res.dataMaxLen = JLP_DEFAULT_BUFSIZE;
    }

    if(!(curl = curl_easy_init())) {
        error = JLP_ERROR_MEMORY;
        goto ERROR;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

    status = curl_easy_perform(curl);

    if(!status) {
        res.data[res.dataLen] = 0;
        *data = res.data;
    } else {
        error = JLP_ERROR_REQUEST;
        goto ERROR;
    }

ERROR:
    curl_easy_cleanup(curl);
    return error;
}
static JLP_Result *jlp_result_create() {
    JLP_Result *res = NULL;
    if(!(res = JLP_Malloc(sizeof(JLP_Result)))) {
        goto ERROR;
    }
    return res;
ERROR:
    JLP_Result_Dispose(res);
    return NULL;
}
static JLP_Error jlp_parse(char *xml, xmlDoc **dom) {
    JLP_Error error = JLP_ERROR_NONE;
    xmlDoc *tmpDom = NULL;

    tmpDom = xmlReadMemory(xml, strlen(xml), NULL, "utf-8", 0);

    /* result */
    *dom = tmpDom;
    return error;
}
JLP_Error JLP_Core_Analyze(JLP_Context *ctx, JLP_Result **res) {
    JLP_Error error = JLP_ERROR_NONE;
    JLP_Result *tmpRes = NULL;
    char *url = NULL;
    char *data = NULL;
    {/* get NL-processing result */
        if((error = jlp_requst_url_create(ctx, &url))) {
            goto ERROR;
        }
        puts(url);

        if((error = jlp_http_get(url, &data))) {
            goto ERROR;
        }
    }
    if(!(tmpRes = jlp_result_create())) {
        error = JLP_ERROR_MEMORY;
        goto ERROR;
    }
    puts(data);
     if((error = jlp_parse(data, &(tmpRes -> dom)))) {
         goto ERROR;
     }

    /* result */
    *res = tmpRes;

    JLP_Free(url);
    JLP_Free(data);
    return error;
ERROR:
    JLP_Free(url);
    JLP_Free(data);
    JLP_Result_Dispose(tmpRes);
    return error;
}
void JLP_Result_Dispose(JLP_Result *res) {
    if(res) {
        xmlFreeDoc(res -> dom);
        JLP_Free(res);
    }
}
static xmlElement *jlp_element_getChildElement(xmlElement *parent, char *childName) {
    xmlNode *childNode = parent -> children;
    while(childNode) {
        if(childNode -> type == XML_ELEMENT_NODE) {
            if(!strcmp((char *)childNode -> name, childName)) {
                break;
            }
        }
        childNode = childNode -> next;
    }
    return (xmlElement *)childNode;
}
JLP_Result_Content *JLP_Result_GetMaResult(JLP_Result *res) {
    xmlElement *element_result_set = (xmlElement *)res -> dom -> children;
    xmlElement *ma_result = jlp_element_getChildElement(element_result_set, "ma_result");
    return (JLP_Result_Content *)ma_result;
}
int JLP_Result_Count(JLP_Result_Content *res) {
    xmlElement *parent = (xmlElement *)res;
    xmlElement *total_count = jlp_element_getChildElement(parent, "total_count");
    int count = atoi((char *)total_count -> children -> content);
    return count;
}
int JLP_Result_FilteredCount(JLP_Result_Content *res) {
    xmlElement *parent = (xmlElement *)res;
    xmlElement *filtered_count = jlp_element_getChildElement(parent, "filtered_count");
    int count = atoi((char *)filtered_count -> children -> content);
    return count;
}
JLP_Word *JLP_Result_GetWord(JLP_Result_Content *res) {
    xmlElement *parent = (xmlElement *)res;
    xmlElement *wordList = NULL;
    xmlElement *word = NULL;
    if(!(wordList = jlp_element_getChildElement(parent, "word_list"))) {
        goto ERROR;
    }
    if(!(word = jlp_element_getChildElement(wordList, "word"))) {
        goto ERROR;
    }
    return (JLP_Word *)word;
ERROR:
    return (JLP_Word *)NULL;
}
JLP_Word *JLP_Result_GetNextWord(JLP_Word *word) {
    xmlElement *wordElement = (xmlElement *)word;
    return (JLP_Word *)wordElement -> next;
}
char *JLP_Word_GetSurface(JLP_Word *word) {
    xmlElement *wordElement = (xmlElement *)word;
    xmlElement *surface = NULL;
    if(!(surface = jlp_element_getChildElement(wordElement, "surface"))) {
        goto ERROR;
     }
    return (char *)surface -> children -> content;
ERROR:
    return NULL;
}
char *JLP_Word_GetReading(JLP_Word *word) {
    xmlElement *wordElement = (xmlElement *)word;
    xmlElement *reading = NULL;
    if(!(reading = jlp_element_getChildElement(wordElement, "reading"))) {
        goto ERROR;
    }
    return (char *)reading -> children -> content;
ERROR:
    return NULL;
}
char *JLP_Word_GetPos(JLP_Word *word) {
    xmlElement *wordElement = (xmlElement *)word;
    xmlElement *pos = NULL;
    if(!(pos = jlp_element_getChildElement(wordElement, "pos"))) {
        goto ERROR;
    }
    return (char *)pos -> children -> content;
ERROR:
    return NULL;
}
char *JLP_Word_GetBaseform(JLP_Word *word) {
    xmlElement *wordElement = (xmlElement *)word;
    xmlElement *baseform = NULL;
    if(!(baseform = jlp_element_getChildElement(wordElement, "baseform"))) {
        goto ERROR;
    }
    return (char *)baseform -> children -> content;
ERROR:
    return NULL;
}
int JLP_Word_GetCount(JLP_Word *word) {
    xmlElement *wordElement = (xmlElement *)word;
    xmlElement *count = NULL;
    if(!(count = jlp_element_getChildElement(wordElement, "count"))) {
        goto ERROR;
    }
    return atoi((char *)count -> children -> content);
ERROR:
    return -1;
}
