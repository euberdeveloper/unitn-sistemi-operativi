#include "logger.h"

int main() {
    log_debug("Das ist nur ein Entwurf");
    log_error("Das ist nur ein Entwurf");
    log_warning("Das ist nur ein Entwurf");
    log_success("Das ist nur ein Entwurf");
    log_info("Das ist nur ein Entwurf");

    log_debug_ctx("Das ist nur ein Entwurf", "CONTEXT");
    log_error_ctx("Das ist nur ein Entwurf", "CONTEXT");
    log_warning_ctx("Das ist nur ein Entwurf", "CONTEXT");
    log_success_ctx("Das ist nur ein Entwurf", "CONTEXT");
    log_info_ctx("Das ist nur ein Entwurf", "CONTEXT");

    return 0;
}