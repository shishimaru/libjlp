#ifndef JLP_H
#define JLP_H

#include "jlp/jlp_common.h"

/**
 * Type of context.
 */
typedef struct JLP_Context JLP_Context;
/**
 * Type of result.
 */
typedef struct JLP_Result JLP_Result;
/**
 * Type of result content.
 */
typedef struct xmlElement JLP_Result_Content;
/**
 * Type of analyzed word.
 */
typedef struct xmlElement JLP_Word;

/**
 * Create a context.
 * @param appid[in] application id published from yahoo.
 * @return created context.
 */
JLP_Context *JLP_Context_Create(char *appid);
/**
 * Set a source sentence which will be analyzed.
 * @param ctx[in] context
 * @param sentence[in] source sentence(not copied)
 */
void JLP_Context_SetSentence(JLP_Context *ctx, char *sentence);
/**
 * Dispose the context.
 * @param ctx[in] context
 */
void JLP_Context_Dispose(JLP_Context *ctx);
/**
 * Set result type of ma, uniq.
 * @param ctx[in] context
 * @param ma[in] ma
 * @param uniq[in] uniq
 */
void JLP_Context_SetResults(JLP_Context *ctx, JLP_Bool ma, JLP_Bool uniq);
/**
 * Set the kind of response contents.
 * @param ctx[in] context
 * @param surface[in] specify to include surface
 * @param reading[in] specify to include reading
 * @param pos[in] specify to include pos
 * @param baseform[in] specify to include baseform
 * @param feature[in] specify to include feature
 */
void JLP_Context_SetResponse(JLP_Context *ctx, JLP_Bool surface,
        JLP_Bool reading, JLP_Bool pos, JLP_Bool baseform, JLP_Bool feature);
/**
 * Set a filter.
 * @param ctx[in] context
 * @param filter[in] filter string
 * @return error code
 */
JLP_Error JLP_Context_SetFilter(JLP_Context *ctx, char *filter);
/**
 * Set a ma filter.
 * @param ctx[in] context
 * @param ma_filter[in] ma filter
 * @return error code
 */
JLP_Error JLP_Context_SetMaFilter(JLP_Context *ctx, char *ma_filter);
/**
 * Set a uniq response
 * @param ctx[in] context
 * @param uniq_response[in] uniq response
 * @return error code
 */
JLP_Error JLP_Context_SetUniqResponse(JLP_Context *ctx, char *uniq_response);
/**
 * Set uniq filter
 * @param ctx[in] context
 * @param uniq_filter[in] uniq filter
 * @return error code
 */
JLP_Error JLP_Context_SetUniqFilter(JLP_Context *ctx, char *uniq_filter);
/**
 * Set uniq by baseform
 * @param ctx[in] context
 * @param uniq_by_baseform[in] uniq by baseform
 * @return error code
 */
JLP_Error JLP_Context_SetUniqByBaseform(JLP_Context *ctx, char *uniq_by_baseform);

/**
 * Send a natural language processing request and analyze the result.
 * @param ctx[in] context
 * @param res[out] result
 * @return error code
 */
JLP_Error JLP_Core_Analyze(JLP_Context *ctx, JLP_Result **res);
/**
 * Dispose the result.
 * @param res result
 * @return error code
 */
void JLP_Result_Dispose(JLP_Result *res);
/**
 * Get a ma result.
 * @param res[in] result
 * @return result content
 */
JLP_Result_Content *JLP_Result_GetMaResult(JLP_Result *res);
/**
 * Get the total number of the results.
 * @param res[in] result content
 * @return the total number of the result
 */
int JLP_Result_Count(JLP_Result_Content *res);
/**
 * Get the total number of the filtered results.
 * @param res[in] result content
 * @return the total number of the filtered result
 */
int JLP_Result_FilteredCount(JLP_Result_Content *res);
/**
 * Get a result word of the result content.
 * @param res[in] result content
 * @return a result word
 */
JLP_Word *JLP_Result_GetWord(JLP_Result_Content *res);
/**
 * Get a next result word of the word.
 * @param word[in] word
 * @return a next word
 */
JLP_Word *JLP_Result_GetNextWord(JLP_Word *word);
/**
 * Get the surface of the word.
 * @param word[in] word
 * @return the surface
 */
char *JLP_Word_GetSurface(JLP_Word *word);
/**
 * Get the reading of the word.
 * @param word[in] word
 * @return the reading
 */
char *JLP_Word_GetReading(JLP_Word *word);
/**
 * Get the pos of the word.
 * @param word[in] word
 * @return the pos
 */
char *JLP_Word_GetPos(JLP_Word *word);
/**
 * Get the baseform of the word.
 * @param word[in] word
 * @return the baseform
 */
char *JLP_Word_GetBaseform(JLP_Word *word);
/**
 * Get the count of the word.
 * @param word[in] word
 * @return the count
 */
int JLP_Word_GetCount(JLP_Word *word);

#endif /* JLP_H */
