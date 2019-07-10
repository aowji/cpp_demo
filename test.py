from subprocess import run
import os

pairs = {}
pairs[0.01] = "壹分"
pairs[0.1] = "壹角"
pairs[0.14] = "壹角肆分"
pairs[1] = "壹元整"
pairs[1.03] = "壹元叁分"
pairs[10] = "壹拾元整"
pairs[13] = "壹拾叁元整"
pairs[100] = "壹佰元整"
pairs[1000] = "壹仟元整"
pairs[1899] = "壹仟捌佰玖拾玖元整"
pairs[1899.99] = "壹仟捌佰玖拾玖元玖角玖分"
pairs[1005] = "壹仟零伍元整"
pairs[1025] = "壹仟零贰拾伍元整"
pairs[10000] = "壹万元整"
pairs[10023078] = "壹仟零贰万叁仟零柒拾捌元整"
pairs[10023078.06] = "壹仟零贰万叁仟零柒拾捌元陆分"


def upper(num):
    prs = run(['build/Debug/chy_upper.exe', str(num)], capture_output=True)
    return prs.stdout.decode('utf8').strip(os.linesep)

failed = []
for k,v in pairs.items():
    u = upper(k)
    if u != v:
        failed.append(k)
        print(f"failed: '{k}', '{v}', '{u}'")

if len(failed) == 0:
    print("testing, all passed.")
