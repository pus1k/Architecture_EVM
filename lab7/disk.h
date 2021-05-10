#ifndef DISK
#define DISK

typedef struct {
    unsigned int address;
} tLBA;

typedef struct {
    unsigned int C;
    unsigned int H;
    unsigned int S;
    unsigned int address;
} tCHS;

typedef struct {
    unsigned int C;
    unsigned int H;
    unsigned int S;
    unsigned int address;
} tLARGE;

typedef struct {
    unsigned int C;
    unsigned int H;
    unsigned int S;
    unsigned int address;
} tIDECHS;

int g_lba2chs(tLBA geometry, tCHS* tweak)
{
    tCHS* temp = new tCHS;
    temp.S = 63;
    unsigned int tmp = geometry.address / 63;
    unsigned int tmph = tmp / 1023;
    for (int i = 1; i < 9; i++) {
        if (tmph <= pow(2, i)) {
            temp.H = pow(2, i);
            break;
        }
    }
    temp.C = tmp / temp.H;
    tweak = temp;
    return 1;
}
int g_lba2large(tLBA geometry, tLARGE* tweak)
{
    tCHS* tempchs;
    tLARGE* temp = new tLARGE;
    g_lba2chs(geometry, tempchs);
    temp.C = tempchs.C / 2;
    temp.H = tempchs.H * 2;
    temp.S = tempchs.S;
    tweak = temp;
    return 1;
}
int g_lba2idechs(tLBA geometry, tIDECHS* tweak)
{
    tCHS* tempchs;
    tIDECHS* temp = new tIDECHS;
    g_lba2chs(geometry, tempchs);
    if (tempchs.C > 1024) {
        temp.C = = 1024;
    } else {
        temp.C = tempchs.C;
    }
    if (tempchs.H > 16) {
        temp.H = 16;
    } else {
        temp.H = tempchs.H;
    }
    if (temp.S > 63) {
        temp.S = 63;
    } else {
        temp.S = tempchs.S;
    }
    tweak = temp;
    return 1;
}
int g_chs2large(tCHS geometry, tLARGE* tweak)
{
    tLARGE* temp = new tLARGE;
    temp.S = geometry.S;
    temp.H = geometry.H / 2;
    temp.C = geometry.C * 2;
    tweak = temp;
    return 1;
}
int g_chs2lba(tCHS geometry, tLBA* tweak)
{
    tweak.address = (geometry.ca * geometry.H + geometry.ha) * geometry.S + geometry.sa - 1;
}
int g_chs2idechs(tIDECHS geometry, tLBA* tweak);
int g_large2chs(tLARGE geometry, tCHS* tweak);
int g_large2idechs(tLARGE geometry, tIDECHS* tweak);
int g_large2lba(tLARGE geometry, tLBA* tweak);
int g_idechs2chs(tIDECHS geometry, tCHS* tweak);
int g_idechs2lagre(tIDECHS geometry, tLARGE* tweak);
int g_idechs2lba(tIDECHS geometry, tLBA* tweak);

// int a_lba2chs(tCHS geometry, tLBA, tCHS*);
// tCHS* temp = new tCHS;
//     temp.sa = (geometry.address % S) + 1;
//     temp.ha = ((geometry.address - temp.sa + 1) / S) % H;
//     temp.ca = (geometry.address - temp.sa + 1 - temp.ha * S) / H * S;
//     tweak = temp;
//     return 1;
// int a_lba2large(tLARGE geometry, tLBA, tLARGE*);
// int a_lba2idechs(tIDECHS geometry, tLBA, tIDECHS*);
// int a_chs2lba(tCHS geometry, tCHS, tLBA*);
// int a_large2lba(tLARGE geometry, tLARGE, tLBA*);
// int a_idechs2lba(tIDECHS geometry, tIDECHS, tLBA*);
// int a_large2chs(tLARGE geometry1, tCHS geometry2, tLARGE, tCHS*);
// int a_large2idechs(tLARGE geometry1, tIDECHSgeometry2, tLARGE, tIDECHS*);
// int a_chs2large(tCHS geometry1, tLARGE geometry2, tCHS, tLARGE*);
// int a_idechs2large(tIDECHS geometry1, tLARGEgeometry2, tIDECHS, tLARGE*);
// int a_chs2idechs(tCHS geometry1, tIDECHS geometry2, tCHS, tIDECHS*);
// int a_idechs2chs(tIDECHS geometry1, tCHS geometry2, tIDECHS, tCHS*);

#endif