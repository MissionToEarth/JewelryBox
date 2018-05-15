//
//  KeyStore.cpp
//  BULL iOS
//
#include "KeyStore.hpp"
#include <string.h>

std::string KeyStore::getStorageKey(KeyStore::Type type)
{
    char *s = "pn;bG_24BI3{rQTqjhe7YFOt_Sp2=[xv<6gmq4[NU/1J[+Y:cucxABCDEFG9J6x]-oS]1ID`[Noh|Ud-]fUO=D,wCxSgi{zgp_,Y1ctVx@9keyRGBUDFPP96gtL4PqdJlR?Ocd^;5>@}FZ>p/HPu}2a@YT]w8T?J|6nfAV6g|py`YvueAaaaaaaaaaaaaZj}tXk<phwr*j]+aTZ6JSCB,o7fPK8,<[yRzt;MolX0hJx-jZ+_tlK\mB[.a4V}P^].cE0+:apw[j}s`K|jWAbbbbbbbbbbbbbbZ<Hay+z+04F|Nc.T`RnD,[C_U3mJ{FLH6X+n1otOrCSLF0_fViA<b?Z`e/aQ@[o-A.<Y3.vs7}*Slqtb4{wKZo:AccccccccccccccccccccZ2Q{S-p-]kRo/{od[H[Mc34dopG\ulX3p^O=YZRV{pr@kLyslO2AdddddddddddddddddddddddddddZZ<8jbe=CBcBV<f:|w.s^K7em_Rhnx-pn5{kG";
    switch(type)
    {
        
        case IMAGE:
        {
            char r[8 + 1]="";
            strncpy(r, s + 52, 8);
            return r;
        }

        case STORAGE:
        {
            char r[13 + 1]="";
            strncpy(r, s + 106, 13);
            return r;
        }

        case AAAAA:
        {
            char r[14 + 1]="";
            strncpy(r, s + 176, 14);
            return r;
        }

        case BBBBB:
        {
            char r[16 + 1]="";
            strncpy(r, s + 273, 16);
            return r;
        }

        case CCCCC:
        {
            char r[22 + 1]="";
            strncpy(r, s + 375, 22);
            return r;
        }

        case DDDDD:
        {
            char r[29 + 1]="";
            strncpy(r, s + 447, 29);
            return r;
        }
      
        default:
            break;
    }
    CCASSERT(false, "KeySore::getStorageKey");
    return "";
}