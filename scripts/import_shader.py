import sys
import os

def import_shaders(filename):
    filepath = os.path.dirname(filename)
    filename = os.path.basename(filename)
    writepath = 'build/%s' % filepath;
    os.mkdirs(writepath);
    with open('%s/%s' % (writepath, filename), 'w') as f:
        f.write('foo')
    f.closed

    print('running on %s' % filename, file=sys.stderr)


if __name__ == "__main__:
    import_sharders(sys.argv[1])