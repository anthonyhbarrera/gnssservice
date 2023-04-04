/* 
 * File:   coverageEnable.h
 * Author: Andreu Montiel
 *
 * Created on 15 de agosto de 2015, 20:43
 */

#ifndef COVERAGEENABLE_H
#define COVERAGEENABLE_H

#ifdef COVERAGE_ENABLED

#define COVERAGE_FILE_NAME      "report/coverage"

extern "C" {
#include <stdio.h>
#include <string.h>

extern void __coveragescanner_install(const char *);
extern void  __coveragescanner_filename(const char *name)   ;
extern void __coveragescanner_set_custom_io(char *(*cs_fgets)(char *s, int size, void *stream),int (*cs_fputs)(const char *s, void *stream),void *(*cs_fopenappend)(const char *path),void *(*cs_fopenread)(const char *path),void *(*cs_fopenwrite)(const char *path),int (*cs_fclose)(void *fp),int (*cs_remove)(const char *name))  ;
extern void  __coveragescanner_save(void)   ;



void ShowCoverageSummary(void) {
    FILE *report;
    char filename[1024];
    char buffer[10240];
    char *ptr;
    int cov_total, cov_positive;
    int i;

    unlink(COVERAGE_FILE_NAME ".csexe"); /* Removes previous executions */
    __coveragescanner_save(); /* Saves execution coverage report */

#ifndef UTGT_LEGACY_REPORT_DISABLE
    report = fopen(COVERAGE_FILE_NAME ".csexe", "rb");
    if (report == NULL) {
        printf("\nNo file covered.\n");
        return;
    }
    
    printf("\nCoverage summary (");
#if defined(COVERAGE_MCDC)
    printf("MC/CD metric):\n");
#elif defined(COVERAGE_BRANCH)
    printf("Branch metric):\n");
#else
    printf("undefined metric):\n");
#endif
    while(fgets(buffer, sizeof(buffer), report)) {
        if (buffer[0] == '/') {
            ptr = strchr(buffer, ':');
            if (ptr) ptr = strchr(ptr+1, ':');
            if (ptr) {
                strcpy(filename, ptr+1);
                if (filename[strlen(filename)-1] == '\n') filename[strlen(filename)-1]=0;
                if (filename[strlen(filename)-1] == '\r') filename[strlen(filename)-1]=0;
            } else {
                filename[0]=0;
            }
        } else if (buffer[0] == '\\') {
            cov_total = 0;
            cov_positive = 0;
            for(i=1; buffer[i] != '\r' && buffer[i] != '\n' && buffer[i]; i++) {
                cov_total++;
                if (buffer[i] == '+') cov_positive++;
            }
            printf(" [% 3.1f %%] > %s\n", 100.0*cov_positive / (float)cov_total, filename);
        }
    }
    printf("\n");
    fclose(report);

#endif /* UTGT_LEGACY_REPORT_DISABLE */
}


} /* EXTERN C */

#endif /* COVERAGE_ENABLED */
#endif /* COVERAGEENABLE_H */

