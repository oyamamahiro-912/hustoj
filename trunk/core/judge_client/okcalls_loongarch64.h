#include <sys/syscall.h>
#include <seccomp.h>
#define HOJ_MAX_LIMIT -1

// C/C++ 精简版
int LANG_CV[CALL_ARRAY_SIZE] = {0, 1, 3, 4, 63, 64, 78, 94, 112, 135, 200, 220, 0};
// Java
int LANG_JV[CALL_ARRAY_SIZE] = {48, 56, 63, 78, 94, 112, 134, 163, 220, 0};
// 全局黑名单
int BLACKLIST[CALL_ARRAY_SIZE] = {57, 59, 165, 169, 0};

void setup_seccomp(int* allowed_syscalls) {
    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
    for (int i = 0; allowed_syscalls[i] != 0; i++) {
        seccomp_rule_add(ctx, SCMP_ACT_ALLOW, allowed_syscalls[i], 0);
    }
    for (int i = 0; BLACKLIST[i] != 0; i++) {
        seccomp_rule_add(ctx, SCMP_ACT_KILL, BLACKLIST[i], 0);
    }
    seccomp_load(ctx);
    seccomp_release(ctx);
}

int main() {
    setup_seccomp(LANG_CV); // 为 C/C++ 设置沙箱
    // 运行用户代码
    return 0;
}
