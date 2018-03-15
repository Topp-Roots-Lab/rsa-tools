// This program will safely run rsa-gia as the privileged (setuid) user.
// Each user that wants to run this program must first run "xhost +SI:localuser:<setuid_user>".

// When you install this program on a new Linux system, apply the following steps:
// 1) Implement the java.conf fix in https://bugs.java.com/view_bug.do?bug_id=7157699. (Correction: Replace "ldconfig" with "ldconfig -v".)
// 2) Make sure that the owner of this program is <setuid_user>. Then, set the setuid bit on this program using "chmod".
// 3) Under the home directory of <setuid_user>, create a directory called ".tmp", and make it writable for all users that want to run this program.

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <pwd.h>

using namespace std;

main()
{
  const string displayEnvKey("DISPLAY");
  const char *displayEnvValue = getenv(displayEnvKey.c_str());
  if (displayEnvValue == NULL)
  {
    cerr << "Elevated Launcher: Fatal error: Must be run from a desktop (X Window System) environment." << endl;
    exit(1);
  }
  const string displayEnv = displayEnvKey + "=" + displayEnvValue;
  const char * const envp[] = {displayEnv.c_str(), NULL};

  clearenv();

  const uid_t euid = geteuid();
  const passwd *password = getpwuid(euid);
  string tmpDirArgument("-Djna.tmpdir=");
  tmpDirArgument += password->pw_dir;
  tmpDirArgument += "/.tmp";

  cout << "Elevated Launcher: Running rsa-gia with " << password->pw_name << " permissions." << endl;
  execle("/opt/java/java_default/bin/java", "java", tmpDirArgument.c_str(), "-jar", "/opt/local/bin/gia-java/rsa-gia_new.jar", "/opt/local/bin/gia-java/default.properties", NULL, envp);
}
