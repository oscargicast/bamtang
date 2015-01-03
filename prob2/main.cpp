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

string kFreqLang = "TEOIARNSHLMYUCWDGPFBVKJ";
string kAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


// Returns the frequency of the letter given inside the message.
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

// Sorts pair structure sorted by the second argument.
struct SortPairBySecondArg
{
  bool operator()(const std::pair<char, int> &left,
                  const std::pair<char, int> &right)
  {
    return left.second < right.second;
  }
};

// Gets the freq table of the message given.
string GetFrequencyTable(string message)
{
  string freq_table;
  std::vector< std::pair<char, int> > complete_freq_table;

  // Counts the frequency of each letter of the alphabet.
  for (int i = 0; i < kAlphabet.length(); i++)
  {
    int second = CountLetter(kAlphabet.at(i), message);
    char first = kAlphabet[i];
    complete_freq_table.insert(complete_freq_table.begin() + i,
                               std::make_pair(first, second));
  }
  // Sorts complete_freq_table by letter frequency (second argument).
  std::sort(complete_freq_table.rbegin(), complete_freq_table.rend(),
            SortPairBySecondArg());
  // Filters if letter frequency is 0.
  for (int i = 0; i < kAlphabet.length(); i++)
  {
    if (complete_freq_table[i].second)
      freq_table.push_back(complete_freq_table[i].first);
  }
  return freq_table;
}

// Returns decrypt message.
string DecryptMessage(string message, string freq_lang)
{
  string freq_table = GetFrequencyTable(message);
  int index;

  // Replaces the message freq_lang by the freq_table obtained.
  for (int i = 0; i < message.length(); i++)
  {
    index = freq_table.find(message[i]);
    if (index != std::string::npos)
      message[i] = freq_lang[index];
  }

  return message;
}

int main()
{
  // Normalizes the kAlphabet and kFreqLang to lowercase.
  std::transform(kAlphabet.begin(), kAlphabet.end(), kAlphabet.begin(),
                 ::tolower);
  std::transform(kFreqLang.begin(), kFreqLang.end(), kFreqLang.begin(),
                 ::tolower);

  string message = DecryptMessage(kEncryptedMessage, kFreqLang);
  cout << message << endl;
  return 0;
}