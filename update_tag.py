import os
import subprocess
# VERSION_FILE = 'VERSION'

# if os.path.isfile(VERSION_FILE):
#     with open(VERSION_FILE, 'r') as file:
#         version = file.readline()
#         version = version[1:]
#         version = version.split('.')
# else:
#     version = [0, 1, 0]
# if version is None:
#     version = [0, 1, 0]


last_commit = subprocess.run(['git', 'rev-parse', 'HEAD'], capture_output=True, text=True).stdout.replace('\n', '')
print(f'Last commit is {last_commit}')

current_tag = subprocess.run(['git', 'describe', '--contains', last_commit], capture_output=True, text=True).stdout.replace('\n', '')
print(f'Current tag is {current_tag if current_tag != '' else None}')

if current_tag == '':
    print('Commit doesn\'t have a tag')
    last_tag = subprocess.run(['git', 'describe', '--abbrev=0', '--tags'], capture_output=True, text=True).stdout.replace('\n', '')
    print(f'Last tag is {last_tag}')

    if last_tag == '':
        version = [0, 1, 0]
    else:
        version = [int(i) for i in last_tag[1:].split('.')]

    last_commit_with_last_tag = subprocess.run(['git', 'log', '-1', last_tag], capture_output=True, text=True).stdout.split('\n')[0].split()[1]
    print(f'Last commit of tag {last_tag} is {last_commit_with_last_tag}')
    commits = subprocess.run(['git', 'log', f'{last_commit_with_last_tag}..{last_commit}', '--format=%B'], capture_output=True, text=True).stdout.split('\n\n')[::-1]

    for commit in commits:
        if 'BREAKING CHANGE' in commit or 'feat!' in commit or 'fix!' in commit:
            version[0] += 1
        elif 'feat' in commit:
            version[1] += 1
        elif 'fix' in commit:
            version[2] += 1
    
    print(f'New version is {version}')
else:
    print('Commit does have a tag')


# version_s = f'v{'.'.join([str(i) for i in version])}'
# print(f'New version is {version_s}')
# with open(VERSION, 'w') as file:
#     file.write(version_s)

