#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const string kEncryptedMessage = "\
uid nx, aex jcdjipx iu wzux zp, ta wxtpa jtdaws, ai etkx vis.\n\
dcos zyexdzaxr aex jxdw jezwipijes iu etkzyg nidx aety iyx hts\n\
ai ri aex ptnx aezyg. z zyexdzaxr aeta jezwipijes udin wtdds htww,\n\
hei zp ns exdi tqactwws. z htya ai ntfx dcos cpxdp udxx. z htya ai\n\
gzkx aexn aex udxxrin ai qeiipx. jxijwx tdx rzuuxdxya. jxijwx qeiipx\n\
rzuuxdxya qdzaxdzt. oca zu aexdx zp t oxaaxd hts tniyg ntys\n\
twaxdytazkxp, z htya ai xyqicdtgx aeta hts os ntfzyg za qinuidatowx.\n\
pi aeta'p heta z'kx adzxr ai ri.\n\
z htya ai piwkx jdiowxnp z nxxa zy aex rtzws wzux os cpzyg qinjcaxdp,\n\
pi z yxxr ai hdzax jdigdtnp. os cpzyg dcos, z htya ai qiyqxyadtax aex\n\
aezygp z ri, yia aex ntgzqtw dcwxp iu aex wtygctgx, wzfx patdazyg hzae\n\
jcowzq kizr  pinxaezyg pinxaezyg pinxaezyg ai pts, \"jdzya exwwi hidwr.\"\n\
z vcpa htya ai pts, \"jdzya aezp!\" z riy'a htya tww aex pcddicyrzyg \n\
ntgzq fxshidrp. z vcpa htya ai qiyqxyadtax iy aex atpf. aeta'p aex otpzq\n\
zrxt. pi z etkx adzxr ai ntfx dcos qirx qiyqzpx tyr pcqqzyqa.\n\
scfzezdi ntapcniai. (hhh.tdaznt.qin/zyak/dcos)\n\
";

std::string kFreqLang = "TEOIARNSHLMYUCWDGPFBVKJ";

std::string kAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int CountLetter(char letter, string message)
{
    int cont = 0;
    int found = 0;
    while (true)
    {
        found = message.find(letter, found);
        if (found == std::string::npos)
            break;
        found++;
        cont++;
    }
    return cont;
}

struct sort_pair_second
{
    bool operator()(const std::pair<char, int> &left, const std::pair<char, int> &right)
    {
        return left.second < right.second;
    }
};


string GetFrequencyTable(string message)
{
    string freqLang;
    std::vector< std::pair<char, int> > items;

    for (int i = 0; i < kAlphabet.length(); i++)
    {
        int second = CountLetter(kAlphabet.at(i), message);
        char first = kAlphabet[i];
        items.insert(items.begin() + i, std::make_pair(first, second));
    }
    std::sort(items.rbegin(), items.rend(), sort_pair_second());
    for (int i = 0; i < kAlphabet.length(); i++)
    {
        if (items[i].second)
            freqLang.push_back(items[i].first);
    }
    return freqLang;
}


string DecryptMessage(string message, string freqLang)
{
    int index;
    for (int i = 0; i < message.length(); i++)
    {
        index = freqLang.find(message[i]);
        if (index != std::string::npos)
            message[i] = kFreqLang[index];
    }
    return message;
}

int main()
{
    std::transform(kAlphabet.begin(), kAlphabet.end(), kAlphabet.begin(), ::tolower);
    std::transform(kFreqLang.begin(), kFreqLang.end(), kFreqLang.begin(), ::tolower);

    string freqLang = GetFrequencyTable(kEncryptedMessage);
    string message = DecryptMessage(kEncryptedMessage, freqLang);
    cout << message << endl;
}