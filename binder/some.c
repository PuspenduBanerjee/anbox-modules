#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>

#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + ((c) > 255 ? 255 : (c)))



int main() {
    struct utsname udata;

    if (uname(&udata) != 0) {
        perror("uname");
        return 1;
    }

    printf("Kernel information:\n");
    printf("  System name: %s\n", udata.sysname);
    printf("  Node name: %s\n", udata.nodename);
    printf("  Release: %s\n", udata.release);
    printf("  Version: %s\n", udata.version);
    printf("  Machine: %s\n", udata.machine);

    // Extract major and minor version numbers (simple approach, may need adjustments)
    char *release_copy = strdup(udata.release); // Make a copy to avoid modifying the original
    if (release_copy == NULL) {
        perror("strdup");
        return 1;
    }

    char *token = strtok(release_copy, ".");
    if (token != NULL) {
        printf("  Major version: %s\n", token);
        token = strtok(NULL, ".");
        if (token != NULL) {
           printf("  Minor version: %s\n", token);
        } else {
            fprintf(stderr, "  Warning: Could not parse minor version\n");
        }
    } else {
         fprintf(stderr, "  Warning: Could not parse major version\n");
    }
    free(release_copy); // Free the allocated memory

    printf("Kernel version code: %d\n", KERNEL_VERSION(6,13,0));
    return 0;
}