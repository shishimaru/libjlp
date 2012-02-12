#include <stdio.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "jlp/jlp.h"

/* TOOD : set your application id */
static char *appid ="YOUR APPLICATION ID";

int main(int argc, char *argv[]) {
    JLP_Error error = JLP_ERROR_NONE;
    JLP_Context *ctx = JLP_Context_Create(appid);
    JLP_Context_SetSentence(ctx, "あはは、今日の空はとてもきれいで青いです。");
    JLP_Context_SetResults(ctx, JLP_TRUE, JLP_FALSE);
    JLP_Context_SetResponse(ctx, JLP_TRUE, JLP_TRUE, JLP_TRUE, JLP_FALSE,
            JLP_FALSE);
    JLP_Context_SetFilter(ctx, "1|2|3|4|5|6|7|8|9|10|11|12|13");

    JLP_Result *res;
    if ((error = JLP_Core_Analyze(ctx, &res))) {
        fprintf(stderr, "error:%d\n", error);
        return 1;
    }

    JLP_Result_Content *ma_result = JLP_Result_GetMaResult(res);
    printf("%d\n", JLP_Result_Count(ma_result));
    printf("%d\n", JLP_Result_FilteredCount(ma_result));

    JLP_Word *word = JLP_Result_GetWord(ma_result);
    while (word) {
        puts(JLP_Word_GetSurface(word));
        puts(JLP_Word_GetReading(word));
        puts(JLP_Word_GetPos(word));
        if (JLP_Word_GetBaseform(word)) {
            puts(JLP_Word_GetBaseform(word));
        }
        printf("%d\n", JLP_Word_GetCount(word));
        word = JLP_Result_GetNextWord(word);
    }

    JLP_Context_Dispose(ctx);
    JLP_Result_Dispose(res);
    puts("END");
    return 0;
}
