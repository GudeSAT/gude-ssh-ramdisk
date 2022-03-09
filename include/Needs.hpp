#ifndef Needs_hpp
#define Needs_hpp

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"

const char* identifier = NULL;
const char* version = NULL;
const char* board = NULL;
const std::string Board;
const char* blob = NULL;
std::string input1, input2;

namespace Apple {
  int Needs(){

    std::cout << "[i] 正在快速进行依赖检查..." << '\n';
    sleep(1);

    std::ifstream brew("/usr/local/bin/brew");
    if(!brew) {
      std::cout << "[i] Homebrew没有找到. 正在为你安装..." << '\n';
      system("/bin/bash -c \"$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\"");
    }

    std::ifstream img4("/usr/local/bin/img4");
    if(!img4){
      std::cout << "[i] Img4 没有找到. 正在为你安装..." << '\n';
      system("curl -LO https://github.com/xerub/img4lib/releases/download/1.0/img4lib-2020-10-27.tar.gz");
      system("tar -xzf img4lib-2020-10-27.tar.gz");
      chdir("img4lib-2020-10-27/apple");
      system("cp -v img4 /usr/local/bin");
      chdir("../..");
      system("chmod +x /usr/local/bin/img4");
      system("rm -rf img4lib-2020-10-27 && rm -rf img4lib-2020-10-27.tar.gz");
    }
    std::ifstream img4tool("/usr/local/bin/img4tool");
    if(!img4tool){
      std::cerr << "[!] Img4tool 没有找到. 正在为你安装..." << '\n';
      system("curl -LO https://github.com/tihmstar/img4tool/releases/download/197/buildroot_macos-latest.zip");
      system("unzip buildroot_macos-latest.zip");
      chdir("buildroot_macos-latest");
      system("rsync --ignore-existing -avhuK ./usr \"/\"");
      chdir("..");
      system("chmod +x /usr/local/bin/img4tool");
      system("rm -rf buildroot_macos-latest.zip && rm -rf buildroot_macos-latest");
    }
    std::ifstream kpatcher("/usr/local/bin/Kernel64Patcher");
    if(!kpatcher){
      std::cerr << "[!] Kernel64Patcher 没有找到. 正在为你安装..." << '\n';
      system("git clone https://github.com/Ralph0045/Kernel64Patcher.git");
      chdir("Kernel64Patcher");
      system("gcc Kernel64Patcher.c -o Kernel64Patcher");
      system("cp -v Kernel64Patcher /usr/local/bin");
      chdir("..");
      system("rm -rf Kernel64Patcher");
    }
    std::ifstream kairos("/usr/local/bin/kairos");
    if(!kairos){
      std::cerr << "[!] Kairos 没有找到. 正在为你安装..." << '\n';
      system("git clone https://github.com/dayt0n/kairos.git");
      chdir("kairos");
      system("make");
      system("cp -v kairos /usr/local/bin");
      chdir("..");
      system("rm -rf kairos");
    }
    std::ifstream irecv("/usr/local/Cellar/libirecovery/1.0.0/bin/irecovery");
    std::ifstream irecovery("/usr/local/bin/irecovery");
    if(!irecv){
      std::cerr << "[!] Irecovery 没有找到. 正在为你安装..." << '\n';
      system("brew install libirecovery");
    }
    else if(!irecovery) {
      system("brew install libirecovery");
    }
    std::ifstream pzb("/usr/local/bin/pzb");
    if(!pzb){
      std::cerr << "[!] Partialzipbrowser 没有找到. 正在为你安装..." << std::endl;
      system("curl -LO https://github.com/tihmstar/partialZipBrowser/releases/download/36/buildroot_macos-latest.zip");
      system("unzip buildroot_macos-latest.zip");
      chdir("buildroot_macos-latest/usr/local/bin");
      system("cp -v pzb /usr/local/bin");
      chdir("../../../..");
      system("chmod +x /usr/local/bin/pzb && rm -rf buildroot_macos-latest.zip && rm -rf buildroot_macos-latest");
    }
    std::ifstream ldid("/usr/local/bin/ldid2");
    if(!ldid) {
      std::cout << "[i] ldid 没有找到. 正在为你安装..." << '\n';
      system("brew install ldid");
    }
    std::ifstream dropbear("/usr/local/bin/dropbearkey");
    if(!dropbear) {
      std::cout << "[i] Dropbear 没有找到. 正在为你安装..." << std::endl;
      system("brew install dropbear");
      }
      std::cout << "[i] 完成!" << '\n';
      system("clear");
  return 0;
}
};

#endif
