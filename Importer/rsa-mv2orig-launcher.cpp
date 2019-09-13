// This program will safely run rsa-mv2orig.py as the privileged (setuid) user.
// Make sure that the owner of this program is the privileged user. Then, set
// the setuid bit on this program using "chmod".

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pwd.h>

using namespace std;

main(int argc, char *argv[])
{
  clearenv();

  const uid_t euid = geteuid();
  const passwd *password = getpwuid(euid);

  char ** const new_argv = new char *[argc];
  new_argv[0] = (char * const) "python";
  new_argv[1] = (char * const) "/opt/local/bin/importer/rsa-mv2orig.py";
  for (int i = 1; i <= argc; ++i)
  {
    new_argv[i + 1] = argv[i];
  }

  cout << "Elevated Launcher: Running rsa-mv2orig.py with " << password->pw_name << " permissions." << endl;
  execv("/usr/bin/python", new_argv);
}
