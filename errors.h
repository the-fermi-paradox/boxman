#ifndef BOXMAN_ERRORS_H
#define BOXMAN_ERRORS_H
static constexpr bool ERROR_LOGGING = true;
void ErrorOut(const char *s, int error_code = 1);
void ErrorWithoutExit(const char *s);
#endif // BOXMAN_ERRORS_H
