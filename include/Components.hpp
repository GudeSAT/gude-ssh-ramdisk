#ifndef Components_hpp
#define Components_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
#include <algorithm>

struct loaders {
  std::string name;
  std::string path;
};

struct info {
  std::string link;
  std::string boardcfg;
  std::string temp;
  std::string ramdisk;
  std::string trustcache;
  std::string Kernel;
  std::string Devicetree;
  std::string rdpath;
  std::string usrin;
  std::string chipid;
};

struct keys {
  std::string Buildid;
  std::string page;
  std::string iv;
  std::string key;
};

namespace load {

info inpt;
info ipsw;
loaders ibss;
loaders ibec;

// parsers didn't work for me so i made this crappy parser

static std::string Time(){
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::string s(30, '\0');
    std::strftime(&s[0], s.size(), "%H:%M:%S", std::localtime(&now));
    return s;
}

void GetManifest(std::string identifier, std::string version){ // gets buildmanifest and ipswlink
mkdir((std::string("GD_") + identifier + "_" + version).c_str(), S_IRWXU);
chdir((std::string("GD_") + identifier + "_" + version).c_str());


 system((std::string("curl -s -LO \"https://api.ipsw.me/v2.1/") + identifier + "/" + version + "/info.json\"").c_str());
  std::ifstream infojson("info.json");
   while(getline(infojson, ipsw.temp)){
    if(ipsw.temp.find("\"url\": \"")!= std::string::npos){
     ipsw.temp.erase(0, 12);
      for(int i = 0; i < ipsw.temp.size(); i++){
       if(ipsw.temp[i] == '"'){
        ipsw.temp.erase(i);
         ipsw.link = ipsw.temp;
          infojson.close();
       }
      }
     }
    }
system((std::string("pzb -g ") + "BuildManifest.plist " + ipsw.link).c_str());
}

std::string iBSS(std::string board){

chdir((std::string("GD_") + identifier + "_" + version).c_str());

std::ifstream Manifest("BuildManifest.plist");
 while(getline(Manifest, ibss.path)) {
  if(ibss.path.find(board) != std::string::npos) {
   for(int i = 0; i < 4000 && getline(Manifest, ibss.path); i++) {
    if(ibss.path.find("iBSS.")!= std::string::npos) {
     Manifest.close();
      ibss.path.erase(0, 14);
       for(int y = 0; y < ibss.path.size(); y++) {
        if(ibss.path[y] == '<') {
         ibss.path.erase(y);
          system((std::string("pzb -g ") + ibss.path + " " + ipsw.link).c_str());
           ibss.path.erase(0, 13);
            ibss.name = ibss.path;
        }
       }
      }
     }
    }
   }
  return ibss.name;
  }

std::string iBEC(std::string board){

chdir((std::string("GD_") + identifier + "_" + version).c_str());

std::ifstream Manifest("BuildManifest.plist");
 while (getline(Manifest, ibec.path)) {
  if(ibec.path.find(board) != std::string::npos) {
   for(int t = 0; t < 4000 && getline(Manifest, ibec.path); t++) {
    if(ibec.path.find("iBEC.") != std::string::npos){
     Manifest.close();
      ibec.path.erase(0, 14);
       for(int e = 0; e < ibec.path.size(); e++) {
        if(ibec.path[e] == '<') {
         ibec.path.erase(e);
          system((std::string("pzb -g ") + ibec.path + " " + ipsw.link).c_str());
           ibec.path.erase(0, 13);
            ibec.name = ibec.path;
         }
        }
       }
      }
     }
    }
  return ibec.name;
   }

std::string buildid(){

keys keyspage;
std::string bldid;

chdir((std::string("GD_") + identifier + "_" + version).c_str());
 std::ifstream json("info.json");
  while(getline(json, bldid)){
   if(bldid.find("\"buildid\": \"") != std::string::npos){
    bldid.erase(0, 16);
     for(int b = 0; b < bldid.size(); b++){
      if(bldid[b] == '"'){
       bldid.erase(b);
       keyspage.Buildid = bldid;
     }
    }
   }
  }
  return keyspage.Buildid;
}

void Getkeyspage(std::string identifier, std::string version){

keys keyspage;

for(int r = 0; r < version.size(); r++){
 if(version[r] == '.'){
  version.erase(r);
   system((std::string("curl -s -LO \"https://www.theiphonewiki.com/wiki/Firmware_Keys/") + version + ".x" + "\"").c_str());
    std::ifstream x((version + ".x"));
     while(getline(x, keyspage.page)){
      if(keyspage.page.find(identifier) != std::string::npos){
       if(keyspage.page.find(buildid()) != std::string::npos){
        x.close();
         for(int w = 0; w < keyspage.page.size(); w++){
          if(keyspage.page[w] == '/'){
           keyspage.page.erase(0, w);
            for(int p = 0; p < keyspage.page.size(); p++){
             if(keyspage.page[p] == '"'){
              keyspage.page.erase(p);
               system((std::string("curl -s \"https://www.theiphonewiki.com") + keyspage.page + "\" -o keys.html").c_str());
                system((std::string("rm -r ") + version + ".x").c_str());
         }
        }
       }
      }
     }
    }
   }
  }
 }
}

std::string kernel(std::string board) {

std::string krn;

chdir((std::string("GD_") + identifier + "_" + version).c_str());
 std::ifstream kern("BuildManifest.plist");
  while(getline(kern, krn)) {
   if(krn.find(board) != std::string::npos) {
    for(int i = 0; i < 3268 && getline(kern, krn); i++) {
     if(krn.find("kernelcache.") != std::string::npos) {
      kern.close();
       krn.erase(0, 14);
        for(int t = 0; t < krn.size(); t++){
         if(krn[t] == '<'){
          krn.erase(t);
           system((std::string("pzb -g ") + krn + " " + ipsw.link).c_str());
            ipsw.Kernel = krn;
       }
      }
     }
    }
   }
  }
return ipsw.Kernel;
}

std::string DeviceTree(std::string board) {

std::string Devtre;

chdir((std::string("GD_") + identifier + "_" + version).c_str());
 std::ifstream manifest("BuildManifest.plist");
  while(getline(manifest, Devtre)) {
   if(Devtre.find(board) != std::string::npos) {
    for(int o = 0; o < 3268 && getline(manifest, Devtre); o++) {
     if(Devtre.find("DeviceTree.") != std::string::npos) {
      manifest.close();
       Devtre.erase(0, 14);
        for(int y = 0; y < Devtre.size(); y++) {
         if(Devtre[y] == '<') {
          Devtre.erase(y);
           system((std::string("pzb -g ") + Devtre + " " + ipsw.link).c_str());
            Devtre.erase(0, 19);
             ipsw.Devicetree = Devtre;
       }
      }
     }
    }
   }
  }
return ipsw.Devicetree;
}

std::string ramdisk(std::string identifier, std::string version) {

std::string rdisk;
chdir((std::string("GD_") + identifier + "_" + version).c_str());

std::ifstream keys("keys.html");
 if(!keys) {
   std::cout << "[e] 脚本似乎无法获取固件密钥，这在低于10.15的macos系统上很常见，不好意思，请将电脑更新至 catalina10.15系统 或者更高系统 (或者使用小写字母p制定设备 :) )" << '\n';
   exit(1);
 }
 while(getline(keys, rdisk)) {
  if(rdisk.find("keypage-restoreramdisk") != std::string::npos) {
   for(int i = 0; i < rdisk.size(); i++) {
    if(rdisk[i] == '0') {
     rdisk.erase(0, i);
      for(int o = 0; o < rdisk.size(); o++) {
       if(rdisk[o] == '<') {
        rdisk.erase(o);
         system((std::string("pzb -g ") + rdisk + " " + ipsw.link).c_str());
          ipsw.ramdisk = rdisk;
      }
     }
    }
   }
  }
 }
return ipsw.ramdisk;
}

std::string trsc(std::string identifier, std::string version) {

chdir((std::string("GD_") + identifier + "_" + version).c_str());
 system((std::string("pzb -g ") + "Firmware/" + ipsw.ramdisk + ".trustcache " + ipsw.link).c_str());
  ipsw.trustcache = (ipsw.ramdisk + ".trustcache");

return ipsw.trustcache;
}
/*
std::string iBSSIV() { // unused functs

keys iBSSiv;

chdir((std::string("GD_") + identifier + "_" + version).c_str());
 std::ifstream keys("keys.html");
  while(getline(keys, iBSSiv.page)) {
   if(iBSSiv.page.find(ibss.name) != std::string::npos) {
    for(int i = 0; i < 3 && getline(keys, iBSSiv.page); i++) {
     if(iBSSiv.page.find("-iv") != std::string::npos){
      for(int i = 0; i < iBSSiv.page.size(); i++) {
       if(iBSSiv.page[i] == '"') {
        iBSSiv.page.erase(0, i);
         for(int u = 0; u < iBSSiv.page.size(); u++) {
          if(iBSSiv.page[u] == '>') {
           iBSSiv.page.erase(0, u); iBSSiv.page.erase(0, 1);
            for(int y = 0; y < iBSSiv.page.size(); y++) {
             if(iBSSiv.page[y] == '<') {
              iBSSiv.page.erase(y); iBSSiv.iv = iBSSiv.page;
           }
          }
         }
        }
       }
      }
     }
    }
   }
  }
return iBSSiv.iv;
}
*/
std::string iBSSIv() {

keys iBSSiv;

chdir((std::string("GD_") + identifier + "_" + version).c_str());
 std::ifstream key("keys.html");
  while(getline(key, iBSSiv.page)) { // stores everything from instream to std::string
   if(iBSSiv.page.find("| file   = iBSS") != std::string::npos) {
    for(int i = 0; i < 3 && getline(key, iBSSiv.page); i++) {
     if(iBSSiv.page.find("iv") != std::string::npos) {
      iBSSiv.page.erase(0, 11);
       iBSSiv.iv = iBSSiv.page;
     }
    }
   }
  }
  return iBSSiv.iv;
}

std::string iBSSKey() {

keys iBSSkey;

chdir((std::string("GD_") + identifier + "_" + version).c_str());
 std::ifstream key("keys.html");
  while(getline(key, iBSSkey.page)) { // stores everything from instream to std::string
   if(iBSSkey.page.find("| file   = iBSS") != std::string::npos) {
    for(int i = 0; i < 3 && getline(key, iBSSkey.page); ++i) {
     if(iBSSkey.page.find("key") != std::string::npos) {
      iBSSkey.page.erase(0, 11);
       iBSSkey.key = iBSSkey.page;
     }
    }
   }
  }
  return iBSSkey.key;
}
/*
std::string iBSSKEY() {

keys iBSSkey;

chdir((std::string("GD_") + identifier + "_" + version).c_str());
 std::ifstream keys("keys.html");
  while(getline(keys, iBSSkey.page)) {
   if(iBSSkey.page.find(ibss.name) != std::string::npos) {
    for(int i = 0; i < 3 && getline(keys, iBSSkey.page); i++) {
     if(iBSSkey.page.find("-key") != std::string::npos){
      for(int i = 0; i < iBSSkey.page.size(); i++) {
       if(iBSSkey.page[i] == '"') {
        iBSSkey.page.erase(0, i);
         for(int u = 0; u < iBSSkey.page.size(); u++) {
          if(iBSSkey.page[u] == '>') {
           iBSSkey.page.erase(0, u); iBSSkey.page.erase(0, 1);
            for(int y = 0; y < iBSSkey.page.size(); y++) {
             if(iBSSkey.page[y] == '<') {
              iBSSkey.page.erase(y); iBSSkey.key = iBSSkey.page;
           }
          }
         }
        }
       }
      }
     }
    }
   }
  }
return iBSSkey.key;
}
*/
std::string iBECIV() {

keys iBECiv;

chdir((std::string("GD_") + identifier + "_" + version).c_str());
 std::ifstream keys("keys.html");
  while(getline(keys, iBECiv.page)) {
   if(iBECiv.page.find(ibec.name) != std::string::npos) {
    for(int i = 0; i < 3 && getline(keys, iBECiv.page); i++) {
     if(iBECiv.page.find("-iv") != std::string::npos){
      for(int i = 0; i < iBECiv.page.size(); i++) {
       if(iBECiv.page[i] == '"') {
        iBECiv.page.erase(0, i);
         for(int u = 0; u < iBECiv.page.size(); u++) {
          if(iBECiv.page[u] == '>') {
           iBECiv.page.erase(0, u); iBECiv.page.erase(0, 1);
            for(int y = 0; y < iBECiv.page.size(); y++) {
             if(iBECiv.page[y] == '<') {
              iBECiv.page.erase(y); iBECiv.iv = iBECiv.page;
           }
          }
         }
        }
       }
      }
     }
    }
   }
  }
return iBECiv.iv;
}

std::string iBECKEY() {

keys iBECkey;

chdir((std::string("GD_") + identifier + "_" + version).c_str());
 std::ifstream keys("keys.html");
  while(getline(keys, iBECkey.page)) {
   if(iBECkey.page.find(ibec.name) != std::string::npos) {
    for(int i = 0; i < 3 && getline(keys, iBECkey.page); i++) {
     if(iBECkey.page.find("-key") != std::string::npos){
      for(int i = 0; i < iBECkey.page.size(); i++) {
       if(iBECkey.page[i] == '"') {
        iBECkey.page.erase(0, i);
         for(int u = 0; u < iBECkey.page.size(); u++) {
          if(iBECkey.page[u] == '>') {
           iBECkey.page.erase(0, u); iBECkey.page.erase(0, 1);
            for(int y = 0; y < iBECkey.page.size(); y++) {
             if(iBECkey.page[y] == '<') {
              iBECkey.page.erase(y); iBECkey.key = iBECkey.page;
           }
          }
         }
        }
       }
      }
     }
    }
   }
  }
return iBECkey.key;
}

int Help() {
  std::cout << "用法:" << std::endl;
  std::cout << "\t-d <设备类型>" << std::endl;
  std::cout << "\t-i <系统版本>" << std::endl;
  std::cout << "\t-b <硬件模型>" << std::endl;
  std::cout << "\t-s <shsh文件>" << std::endl;
  return 0;
}

void Cleaner(std::string identifier, std::string version) {
chdir((std::string("GD_") + identifier + "_" + version).c_str());
system("rm BuildManifest.plist && rm info.json && rm keys.html");
system("rm ibss.raw && rm ibss.pwn");
system("rm ibec.raw && rm ibec.pwn");
system("rm kernel.raw && rm kernel.im4p && rm kernel.patched");
}

void check(std::string version) {

if(version == "15.0" || version == "15.0.1" || version == "15.0.2" || version == "15.1" || version == "15.2" || version == "15.3" || version == "15.3.1" || version == "15.4"){
  system("Kernel64Patcher kernel.raw kernel.patched -a -s -r");
  system("img4tool -c kernel.im4p -t rkrn kernel.patched --compression complzss");
  system("img4tool -c KernelCache.img4 -p kernel.im4p");
  system("img4 -i KernelCache.img4 -M IM4M");
  std::cout << "[!] 完成!" << std::endl << std::endl;
    
}
    
else {
  system("Kernel64Patcher kernel.raw kernel.patched -a");
  system("img4tool -c kernel.im4p -t rkrn kernel.patched --compression complzss");
  system("img4tool -c KernelCache.img4 -p kernel.im4p");
  system("img4 -i KernelCache.img4 -M IM4M");
  std::cout << "[!] 完成!" << std::endl << std::endl;
}
}
    
int Ramdisk(std::string version) {
  std::ifstream iBSS((std::string("Patched") + "_" + identifier + "_" + version + "/iBSS.img4").c_str());
  if(!iBSS){
    std::cerr << "发生一些其他问题，请仔细检查一下. 退出......" << std::endl;
    exit(1);
  }
  chdir((std::string("Patched") + "_" + identifier + "_" + version).c_str());
  sleep(2);
  std::cout << RED << Time() << RESET << " 发送 iBSS..." << std::endl;
  system("irecovery -f iBSS.img4");
  system("irecovery -f iBSS.img4");
  std::cout << RED << Time() << RESET << " 完成!" << std::endl << std::endl;
  sleep(2);
  std::cout << RED << Time() << RESET << " 发送 iBEC..." << std::endl;
  system("irecovery -f iBEC.img4");
  system("irecovery -f iBEC.img4");
  std::cout << RED << Time() << RESET << " 完成!" << std::endl << std::endl;
  sleep(2);
  system("irecovery -c \"go\"");
  sleep(2);
  std::cout << RED << Time() << RESET << " 发送 Ramdisk..." << std::endl;
  system("irecovery -f ramdisk");
  std::cout << RED << Time() << RESET << " 完成!" << std::endl << std::endl;
  sleep(2);
  system("irecovery -c \"ramdisk\"");
  sleep(2);
  std::cout << RED << Time() << RESET << " 发送 DeviceTree..." << std::endl;
  system("irecovery -f DeviceTree.img4");
  std::cout << RED << Time() << RESET << " 完成!" << std::endl << std::endl;
  sleep(2);
  system("irecovery -c \"devicetree\"");
  sleep(2);
  std::cout << RED << Time() << RESET << " 发送 TrustCache..." << std::endl;
  system("irecovery -f Trustcache.img4");
  std::cout << RED << Time() << RESET << " 完成!" << std::endl << std::endl;
  sleep(2);
  system("irecovery -c \"firmware\"");
  sleep(2);
  std::cout << RED << Time() << RESET << " 发送 Kernelcache..." << std::endl;
  system("irecovery -f KernelCache.img4");
  std::cout << RED << Time() << RESET << " 完成!" << std::endl;
  sleep(2);
  system("irecovery -c \"bootx\"");

  std::cout << "设备现在应该正在启动引导至 restoreramdisk. 现在在终端运行 iproxy 2222 44 然后 打开另一个终端输入 'ssh root@localhost -p 2222' 连接设备 by https://www.goodsat.cn 古德制作:)" << std::endl;
  return 0;
  }

void mount() {

  FILE* rd = popen("hdiutil attach ramdisk.dmg", "r");
  char path[200];

  while(fgets(path, sizeof(path)-22, rd) != NULL) {
   ipsw.rdpath = path;
    pclose(rd);
     ipsw.rdpath.erase(std::remove(ipsw.rdpath.begin(), ipsw.rdpath.end(), '\n'), ipsw.rdpath.end());
      ipsw.rdpath.erase(0, 15);
       ipsw.rdpath.erase(0, ' ');
        ipsw.rdpath.erase(0, 6);

  }
}
std::string tolower(std::string Boardid){
 std::for_each(Boardid.begin(), Boardid.end(), [](char & conv) {
   conv = ::tolower(conv);
 });
 return Boardid;
}

void Pwndevice() {

std::string chipid;

std::cout << "[?] 输入你的cpu型号。(A6/A7/A8x/A9/A10/A10x/A11)? ";
std::cin >> chipid;

while(1) {
  if(chipid == "A10" || chipid == "0x8010" || chipid == "t8010" || chipid == "A10X" || chipid == "0x8011" || chipid == "t8011" || chipid == "S5L8960" || chipid == "A7" || chipid == "S5L8965"){
    system("git clone https://github.com/MatthewPierson/ipwndfu_public");
    chdir("ipwndfu_public");
    std::cout << "[!] 必须将手机处于DFU模式.必须将手机处于DFU模式.必须将手机处于DFU模式 !!" << '\n';
    sleep(10);
    system("clear");
    std::cout << "[i] 将设备处于特殊pwned DFU 模式..." << '\n';
    system("sudo ./ipwndfu -p");
    sleep(2);
    std::cout << "[i] 移除签名认证..." << '\n';
    system("sudo python rmsigchks.py");
    break;
  }
  else if(chipid == "A11" || chipid == "t8015" || chipid == "0x8015") {
    system("git clone https://github.com/m1stadev/ipwndfu-8015");
    chdir("ipwndfu-8015");
    std::cout << "[!] 必须将手机处于DFU模式.必须将手机处于DFU模式.必须将手机处于DFU模式!!" << '\n';
    sleep(10);
    system("clear");
    std::cout << "[i] 将设备处于特殊pwned DFU 模式..." << '\n';
    system("sudo ./ipwndfu -p");
    sleep(2);
    std::cout << "[i] 移除签名认证..." << '\n';
    system("sudo ./ipwndfu --patch");
    break;
  }
  else if(chipid == "A9" || chipid == "s8000" || chipid == "S8000" || chipid == "S8003" || chipid == "s8003" || chipid == "S5L8950" || chipid == "A6") {
    system("git clone https://github.com/dora2-iOS/ipwnder_lite.git");
    chdir("ipwnder_lite");
    std::cout << "[!] 必须将手机处于DFU模式.必须将手机处于DFU模式.必须将手机处于DFU模式!!" << '\n';
    sleep(10);
    system("clear");
    std::cout << "[i] 将设备处于特殊pwned DFU 模式并移除签名认证..." << '\n';
    system("make && ./ipwnder_macosx -p");
    break;
  }
  else if(chipid == "A8" || chipid == "A8X" || chipid == "T7000" || chipid == "T7001" || chipid == "t7000" || chipid == "t7001" || chipid == "A8x") {
    system("git clone https://github.com/0x7ff/eclipsa.git");
    chdir("eclipsa");
    system("make && ./eclipsa");
    break;
  }
  else {
    std::cout << "[?] 你输入了什么，输入错误?? '" << chipid << "'???" << '\n';
  }
 }
}
};
#endif /* Components_hpp */
