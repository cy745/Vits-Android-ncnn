#include <iostream>
#include <cstring>
#include "../mecab/mecab.h"
#include "../mecab2njd/mecab2njd.h"
#include "../text2mecab/text2mecab.h"
#include "../njd/njd.h"
#include "../njd_set_pronunciation/njd_set_pronunciation.h"
#include "../njd_set_digit/njd_set_digit.h"
#include "../njd_set_accent_phrase/njd_set_accent_phrase.h"
#include "../njd_set_accent_type/njd_set_accent_type.h"
#include "../njd_set_unvoiced_vowel/njd_set_unvoiced_vowel.h"
#include "../njd_set_long_vowel/njd_set_long_vowel.h"
#include "../jpcommon/jpcommon.h"
#include "../njd2jpcommon/njd2jpcommon.h"
#include <vector>
#include <locale>
#include <codecvt>
#include <sstream>
#include <android/log.h>

using namespace std;
typedef unsigned char BYTE;

#define TAG "MoeRengMain" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型


std::string utf8_encode(const std::wstring& source);
std::wstring utf8_decode(const std::string& source);

template<typename T> void print_list(T t, int len) {
    std::cout << "[";
    for (int i = 0; i < len; i++) {
        if (i != len - 1) {
            std::cout << int(t[i]) << ",";
        }
        else {
            std::cout << int(t[i]);
        }
    }
    std::cout << "]" << endl;
}

struct Feature {
    wstring string;
    wstring pos;
    wstring pos_group1;
    wstring pos_group2;
    wstring pos_group3;
    wstring ctype;
    wstring cform;
    wstring orig;
    wstring read;
    wstring pron;
    int acc;
    int mora_size;
    wstring chain_rule;
    int chain_flag;
};

wstring njd_node_get_string(NJDNode* node);
wstring njd_node_get_pos(NJDNode* node);
wstring njd_node_get_pos_group1(NJDNode* node);
wstring njd_node_get_pos_group2(NJDNode * node);
wstring njd_node_get_pos_group3(NJDNode * node);
wstring njd_node_get_ctype(NJDNode * node);
wstring njd_node_get_cform(NJDNode * node);
wstring njd_node_get_orig(NJDNode * node);
wstring njd_node_get_read(NJDNode * node);
wstring njd_node_get_pron(NJDNode * node);
int njd_node_get_acc(NJDNode * node);
int njd_node_get_mora_size(NJDNode * node);
wstring njd_node_get_chain_rule(NJDNode * node);
int njd_node_get_chain_flag(NJDNode * node);

class OpenJtalk {
private:
    Mecab* mecab;
    NJD* njd;
    JPCommon* jpcommon;
    void _clear();
public:
    OpenJtalk(const char* path, AssetJNI* asjni);
    ~OpenJtalk();
    vector<Feature*> run_frontend(wstring text);
    vector<wstring> make_label(vector<Feature*> features);
    string words_split(const char*path, const char* inputs, AssetJNI *assetJni);
};
