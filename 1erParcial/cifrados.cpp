#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

// Bandera de Debugging
#ifdef DEBUG
#define LOG_DEBUG(msg) cout << "[DEBUG]" << msg << endl;
#else
#define LOG_DEBUG(msg)
#endif

// Constante que tiene todos los caracteres validos para el cifrado
const string ALPHABETO = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-?";
const unordered_map<char,double> FRECUENCIA_ESPERADA = { 
    {'a',0.082}, {'b',0.015}, {'c',0.028}, {'d',0.043}, 
    {'e',0.127}, {'f',0.022}, {'g',0.020}, {'h',0.061}, 
    {'i',0.070}, {'j',0.0016}, {'k',0.0077}, {'l',0.040}, 
    {'m',0.024}, {'n',0.067}, {'o',0.075}, {'p',0.019}, 
    {'q',0.0012}, {'r',0.060}, {'s',0.063}, {'t',0.091}, 
    {'u',0.028}, {'v',0.0098}, {'w',0.024}, {'x',0.0015}, 
    {'y',0.020}, {'z',0.00074} };

// ====== CIFRADOS
stack<pair<int,char>> eliminar_caracteres_invalidos(string& _s);
void regresar_caracters_invalidos(stack<pair<int,char>> &_stack, string &_s);

// Funcion cifrado y desifrado Cesar que cifra un mensaje en base a una llave numero como desplazamiento
// @input: tienes una frase (_s) y una llave (_k) que mueve (shift) la pos de una letra k veces.
// @output: frase crifrada/desifrada usando cesar
string cifrar_cesar(string _s, int _k);
string decifrar_cesar(string _s, int _k);

// Funcion cifrado y desifrado Vigenere que mueve la pos en base a un cifrado cesar con una palabra llave
// @input: tienes una frase (_s) y una llave (_k) que dependiendo de las palabras que contenga puede shiftear la pos del alfabeto.
// @output: frase crifrada/decifrada usando Vigenere
string cifrar_vigenere(string _s, string _k);
string decifrar_vigenere(string _s, string _k);

//  ====== ANALISIS DE FRECUENCIA
// Cuenta las letras para obtener la frecuencia observada de cada letra valida en el cifrado
// @input: mensaje a obtener
// @output: string con el mensaje ordenado
unordered_map<char,int> obtenerConteo(string& _m);
// Compara las palabras con el ingles y regresa si es que las mas usadas concuerdan con el con letras mas conocidas
// @input: mensaje a obtener
// @output: int con calificacion de similitud a letras mas conocidas
double calcularchiCuadrada(string& _m);

// ======= Crackear el cifrado
// Funcion que obtiene todos los elementos en n
// @input: Obtiene el indice que quiere
// @output: frase crifrada
string obtenerElementoEnPosN(int _idx, int _tamanioClave, string& _m);
// Funcion que intenta hackear el cifrado
// @input: tienes un texto
// @output: el mensaje crackeado
void hackearVigenere(string& _m, int _k);

int main(){
    string caso_1 = "D,NfFtF BtdsC ZHt qFpLOGuoh F UEeC ATLybl j7FtsC BZy Ljk lIyEbBEJr rQCC VOx ewnJM Jvs pX BNnwwQuGusk cu wfFCTNt es XTHMfFCJSq ?PFJHH. zp 0IR bliC et ms AZywp qzSNxtHlWt rTwi DYL fz pVOBqC nFGIfCy Iy 5fLtHIp tsyTLp vBl Iy EbG yTGBooD RuL bzEFMp bqlGu wf syKLxoHlW u No sBZCIp EFJ Jxmsl JF wfGnJHLpk nTH Noo oJ Ftt BzRCGbG xFM ubxlX xx fGEJ JtjGh HIG vB pVOBqC BZy IsonYCvbApSNx io pXNteC pS KNjsmWuq-l j9Bp fvh JBp qCC JMH. DzW yLpk AJLH twh UIK fGzB JHs sDTq IfFz JF IbFENxH uIGT NKfG wQyzbrlXq MssD LIEfGh JM MprzC 6HoHpWLxz HF0I xm FtYGH es uZyzpk EZPH mo AJFHuoi gIK rIp ICvfG BZy xt vFRCEmoyYys ?SD MOFjzwFHMfk pX BNnwwQuGus BZy efDpIu xo f lSIL iomNu toCEFxH vBl FHHuonNIG z sy Ag FjBFYIL us sFAt uFpX u MjliC sXT2 1lY -JSY9 ,?F 9Pit rFG sZGBmzlSNx ?S3f ,?F 7T97X R8P mY,a mPj8 6P 7T97X R8P mY, OOO5 sTik yT yL iIxNFEbBEJt rNwCFq PfMh HBBoulX u Mv AlILx. Kp3 sXtC yT NBfBp Suwb EFJ Pxsk yT NtnDzHIp uoxUIvpliC sCbxlOu tkouFD rpwh JMIfFlYyp z At RuwssnNNt rIp HOEqo ENyGfn";
    string caso_2 ="EA qk sFBmvz rin hg fztsvA Hrnw edAuirzAe np vxFGo DiHuGmpr rx lr AscHrfdFBan tzetyg fCG uEi AeAxcowwau kCmCpgwoFeEBs nHixdl da Ew Eurvkd Gxr vt HiCmer pEaEkC dr fwuztsn CB svqros trswz eA in iCGdF lsl FenrBp qLmFin qqysKmv twbEiohBMeo IGi Dyg? oIlzkonqs nd zHgzko dr yp usH nLmJo Dyg hBMrr i za petfsE, umqiqm sxs xsv uwszs flo Bbr i wmCsphF KeJxstB e vrrt cFAHa Cetd ENe Eirir wg psMivzo cBroluH. Zjo cnqkqoGdF kCn Ceur tBrDm Fuzfq d AB srtCn pycqrH, um FeCipwsp eJkIcui c pwL eJxolqeu xB yuvzHe L wgfC Xhn mv, Dyg ps LoEw qozs ul Ax eJBIvvitd vtbCiBdB yp foOeIvwcBpca Rxczlw itrquoKlF xorn rq ysKmv lsbvp A vszuz ls lnvirl .iE mAbnvirk we Ci Baqe- vsGtz CB jnpqq Htn MqClrrvr rxsum otEeu tIx eJkIcui rhFyetBomrrvh qHmF As rBqrloG lFA HiEepwsL dv uw mBgjlzt, HCs pnvc fCEmF mFa qi UswweIg0aAb Gq sLe DwAeAxq ssGsv 6o vnpkr AtdImk yn qg uCFpzmFoA in kCvitwl Mr hk oo OuvtHa sytlCLon twsGs rdFt dvnsnqitpsq AC DClGicuk Fe KwDe qi husGtv kCn Hr vlDH eEwFmrb Oh Gtcrjo pBv nr AxnFA roF gcesSaJ ls ayxwuop tvvwa ysu kCFbIwG aAgjlGBmFAk eEe fh DBeC uCrrrc B Mt lv mGtnfc fsKrrvro ye ddFua um qaAhcgCq Przscve sxs Ee yipinr rxsLtF mz uAmhrFFe um za rwexsEa rt wnGipgsGtvf 3eAwcqrH qLm sl rvc hz tbLAwvB uwh Jxnzi o atvggwKmve repmfl qHnvkHaE in sFBmvz uoytg soKa xiBaE zgqHtjrf Ze Fsnws Nn GCBeGeBr qHn KwraF qkv tNeIHos qmthqMo vv za petdl VoE uIcue uxsKtv mz gBprh qHnvkHo ymoswH y vt HrrqgqrH gzoonGsp foRo um ssCengoL aC AIeys? SoKa rAsgHvcu AB tvzFiGstlC R tvzAiAet gs BmGwBeE vgvDxtFe Ae nfcooGcv ACbEi go M voDmBcr e irzIerzzo rr go DBsFf Sn pygvHBoE ls srkwqrHs Jm toEqq xBt eEwFmr fqoo we rtImAsu dzKeumroE hg qCLoKzCsk TguC tlxw onqedd Atlo Mz azfkhBMe Jm GeAxkd sQtIiBazipws MeEAC. Ye oxzMiKCr nB iuwoua xzwtnrfr Dxlvik prpgd BB fvAHewepgC xl DwFbB iufCEaIf 7oqsu pwKasiB cBr wqo xxGzssvsp gs AoIzCr L edvCEuKi GoEtthGt. Um FeCipwsp eEBFe rp ulzxntqC dr pc pIEtzBIdj iufIvhv mz gEmvr rxsvADeEefr rx uEiG cumedG we Dq Gaysp RMx, Ew AaAgjhGq QLm ze rwvdG Aatqsnqs c FsLaIqB? Rr ol AxnKm Ae CvgjIGtv mLtEepdrH PFz Eur gcuoCoJ ts dvggq Qxsrzwn rr flABnLBwvB e wq DBntps tEepvtHrDmF dr hqv AxtIwG? Zi fhHNvv G zo zmth rxtvvwdnqgqHx a Ci qaEe? IIx ayq qunrfr Gx mv kCntinr zt srvurrb Go ANcyiqhB xgqwt lFA CjBw nosGoJ ls lnktlAts P xIdr rqwoK eE AIs seefwHnvA In EeujC FuP xscHpkdFq Tvvwa ye rhCK sLmFtr hgo ANnuw QeFetlB xrr mz ayyoqC voE zstEeur rx lr mGcHindl ,eJCztn uwh sE pFjFe PiudFBn Ew orGmexztbr jweA pcv DtlrjFaFb Ux FNdF Mv, rl pr sKa Lvo pEsxrqtczwB, Fmpr GN mrvsrn enhuKe um GayyfdF xn sCsnn spgo t lFA olHqprG GuvDCsk GqpC MeEqo uAe hxsKzr jFuGe vusFeElo qHi pr Gtbzi Aeqmt? oE iEBsnGet wCvaIus ey lqppKo um AaAitd oFiJBCsna vhFFiEw FoztkhBwo GwF cBqrosMo CwG tvvcqHxs um Ai zsekwEao 1Cdn pc hGvuvto lB gqqCvire zo Dyguwt y Cw DrBxgjwt dvAre ueelo tnFAl Ay jkqoE, Dm Eurhg soKauw sn ziflC weC xotvs gvqHlrzk dnrfrAx cLmBtn hg tIx eE uw bEmnooGtv xzaA tqu wFpFvsr EiussMo vv Ai CvkpsK dzik mr lcewt axiFrnhq d uHlGmG ay rkqC voE vscrwkgoweJ mGprgkdzxs umz cBpgjwH. 3qsnGvcv Ax aCmxaoe erB Fi Dwqhvpc uCMan AClB enfoGzrjo a rwexqAaI tCs zytpIElFA voEvquwSauwG dr qkv qHmGiBeEsu gwvivvro NkwdG voE mz nHixrk xsKi zops- vs Fauzso n GgvoKiE "; 
    hackearVigenere(caso_1, 6);
    cout << endl;
    cout <<decifrar_vigenere(caso_1, "Futbol");
    cout << endl;
    hackearVigenere(caso_2, 11);
    cout <<decifrar_vigenere(caso_2, "anecdotario");
    cout << endl;
}

void hackearVigenere(string& _m, int _k){
    vector<vector<int>> candidatos(_k);
    stack<pair<int, char>> invalid = eliminar_caracteres_invalidos(_m);
    for(int i= 0; i < _k; i++){
        string grupo = obtenerElementoEnPosN(i, _k, _m);
        vector<pair<double,int>> resultados_grupo;
        for(int clave = 0; clave < ALPHABETO.size(); clave++){
            string grupo_decifrado = decifrar_cesar(grupo,clave);
            double chi = calcularchiCuadrada(grupo_decifrado);
            resultados_grupo.push_back({chi, clave});
        }
        sort(resultados_grupo.begin(), resultados_grupo.end());
        for(int j = 0; j < 2; j++){
            LOG_DEBUG(resultados_grupo[j].first << " "<< ALPHABETO[resultados_grupo[j].second] << " ");
            candidatos[i].push_back(resultados_grupo[j].second);
        }
    }
    // PROBAR COMBINACIONES
    for(const auto candidato: candidatos){
        for(const auto letra: candidato){
            cout << ALPHABETO[letra] << " ";
        }
        cout << endl;
    }
    regresar_caracters_invalidos(invalid, _m);
}

string cifrar_cesar(string _s, int _k){
    string nueva_frase;
    int valor_circular = ALPHABETO.size();
    for(const auto& letra: _s){
        int pos = ALPHABETO.find(letra);
        nueva_frase += (pos == -1) ? letra: ALPHABETO[(pos + _k)%valor_circular];
    }
    return nueva_frase;
}
string decifrar_cesar(string _s, int _k){
    string nueva_frase;
    int valor_circular = ALPHABETO.size();
    for(const auto& letra: _s){
        int pos = ALPHABETO.find(letra);
        int shift =  (pos - _k + valor_circular)%valor_circular;
        nueva_frase += (pos == -1) ? letra: ALPHABETO[shift];
    }
    return nueva_frase;
}

stack<pair<int,char>> eliminar_caracteres_invalidos(string& _s){
    stack<pair<int, char>> char_invalid;
    for(int i= 0; i < _s.size(); i++){
        if(ALPHABETO.find(_s[i]) == -1){
            char_invalid.push({i, _s[i]});
            _s.erase(i, 1);
        }
    }
    return char_invalid;
}

void regresar_caracters_invalidos(stack<pair<int,char>> &_stack, string &_s){
    while(!_stack.empty()){
        pair<int,char> p = _stack.top();
        _s.insert(p.first, 1, p.second);
        _stack.pop();
    }
}

string cifrar_vigenere(string _s, string _k){
    stack<pair<int, char>> invalid = eliminar_caracteres_invalidos(_s);
    string nueva_frase;
    int valor_circular_llave = _k.size();
    for (int i= 0; i < _s.size(); i++){
        int pos_shift = ALPHABETO.find(_k[i % valor_circular_llave]);
        nueva_frase += cifrar_cesar(string(1,_s[i]), pos_shift);
    }
    regresar_caracters_invalidos(invalid, nueva_frase);
    return nueva_frase;
}

string decifrar_vigenere(string _s, string _k){
    stack<pair<int, char>> invalid = eliminar_caracteres_invalidos(_s);
    string nueva_frase;
    int valor_circular_llave = _k.size();
    for (int i= 0; i < _s.size(); i++){
        int pos_shift = ALPHABETO.find(_k[i % valor_circular_llave]);
        nueva_frase += decifrar_cesar(string(1,_s[i]), pos_shift);
    }
    regresar_caracters_invalidos(invalid, nueva_frase);
    return nueva_frase;
}

string obtenerElementoEnPosN(int _idx, int _longitudLlave, string& _m){
    string valores;
    for(size_t i = _idx; i < _m.size(); i += _longitudLlave){
        valores += _m[i];
    }
    return valores;
}

unordered_map<char,int> obtenerConteo(string& _m){
    unordered_map<char,int> letras_contadas;
    // Cuenta las letras
    for (const auto c : FRECUENCIA_ESPERADA) {
        letras_contadas.insert({c.first, 0});
    }
    for (size_t i = 0; i < _m.size(); i++){
        if (isalpha(_m[i])){
            char letra = tolower(_m[i]);
            letras_contadas[letra] += 1;
        }
    }
    return letras_contadas;
}

double calcularchiCuadrada(string& _m){
    double chi = 0;
    int N = 0;
    unordered_map<char, int> letras_contadas = obtenerConteo(_m);
    for (const auto c : letras_contadas) {
        N += c.second;
    }

    for (const auto letra: FRECUENCIA_ESPERADA){
        // Valor esperado
        double E = letra.second * N;
        int O = letras_contadas[letra.first];
        chi += pow(O - E, 2) / E;
    }
    return chi;
}
