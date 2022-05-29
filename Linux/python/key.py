from subprocess import check_output
import subprocess
import hashlib
import os.path

def gen_license_key():
    result = subprocess.run("cat /var/lib/dbus/machine-id", stdout=subprocess.PIPE, shell=True, check=True)
    machine_id = result.stdout.decode().strip()
    return hashlib.sha512(machine_id.encode('utf-8')).hexdigest()


def check_license(filename):
    if not os.path.isfile(filename):
        return False
    with open(filename, "r") as license:
        if license.readline() == gen_license_key():
            return True
        else:
            return False


def create_license(filename):
    with open(filename, "w+") as license:
        license.write(gen_license_key())


if __name__ == "__main__":
    create_license("license.key")
