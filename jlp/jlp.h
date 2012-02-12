#include "jlp/jlp_common.h"

typedef struct JLP_Context JLP_Context;
typedef struct JLP_Result JLP_Result;
typedef struct xmlElement JLP_Result_Content;
typedef struct xmlElement JLP_Word;

JLP_Context *JLP_Context_Create(char *appid);
void JLP_Context_SetSentence(JLP_Context *ctx, char *sentence);
void JLP_Context_Dispose(JLP_Context *ctx);
void JLP_Context_SetResults(JLP_Context *ctx, JLP_Bool ma, JLP_Bool uniq);
void JLP_Context_SetResponse(JLP_Context *ctx, JLP_Bool surface,
        JLP_Bool reading, JLP_Bool pos, JLP_Bool baseform, JLP_Bool feature);
JLP_Error JLP_Context_SetFilter(JLP_Context *ctx, char *filter);
JLP_Error JLP_Context_SetMaFilter(JLP_Context *ctx, char *ma_filter);
JLP_Error JLP_Context_SetUniqResponse(JLP_Context *ctx, char *uniq_response);
JLP_Error JLP_Context_SetUniqFilter(JLP_Context *ctx, char *uniq_filter);
JLP_Error JLP_Context_SetUniqByBaseform(JLP_Context *ctx, char *uniq_by_baseform);


JLP_Error JLP_Core_Analyze(JLP_Context *ctx, JLP_Result **res);
void JLP_Result_Dispose(JLP_Result *res);

JLP_Result_Content *JLP_Result_GetMaResult(JLP_Result *res);
int JLP_Result_Count(JLP_Result_Content *res);
int JLP_Result_FilteredCount(JLP_Result_Content *res);

JLP_Word *JLP_Result_GetWord(JLP_Result_Content *res);
JLP_Word *JLP_Result_GetNextWord(JLP_Word *word);
char *JLP_Word_GetSurface(JLP_Word *word);
char *JLP_Word_GetReading(JLP_Word *word);
char *JLP_Word_GetPos(JLP_Word *word);
char *JLP_Word_GetBaseform(JLP_Word *word);
int JLP_Word_GetCount(JLP_Word *word);
