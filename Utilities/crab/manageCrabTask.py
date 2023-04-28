#!/usr/bin/python
#-----------------------------------------------
import sys, os, pwd, commands
import optparse, shlex, re
import time
from time import gmtime, strftime
import math

#define function for parsing options
def parseOptions():
    global observalbesTags, modelTags, runAllSteps

    usage = ('usage: %prog [options]\n'
             + '%prog -h for help')
    parser = optparse.OptionParser(usage)

    # input options
    parser.add_option('-t', '--taskDir', dest='TASKDIR', type='string',default='', help='crab task dir')
    parser.add_option('-k', '--kill', dest='KILL', action='store_true', default=False, help='kill jobs')
    parser.add_option('-r', '--resubmit', dest='RESUBMIT', action='store_true',default=False, help='resubmit jobs')
    parser.add_option('-s', '--status', dest='STATUS', action='store_true',default=False, help='status of jobs')
    parser.add_option('-p', '--purge', dest='PURGE', action='store_true',default=False, help='purge jobs (clear crab cache)')
    parser.add_option('--report', dest='REPORT', action='store_true',default=False, help='generate report')
    parser.add_option('-l', '--loop', dest='LOOP', action='store_true',default=False, help='keep doing command every 20 min.')

    # store options and arguments as global variables
    global opt, args
    (opt, args) = parser.parse_args()

# define function for processing the external os commands
def processCmd(cmd, quite = 0):
    #    print cmd
    status, output = commands.getstatusoutput(cmd)
    if (status !=0 and not quite):
        print 'Error in processing command:\n   ['+cmd+']'
        print 'Output:\n   ['+output+'] \n'
    return output

def manage():

    # parse the arguments and options
    global opt, args
    parseOptions()

    taskdir = opt.TASKDIR
    
    while (1):
        print ''
        print ''
    
        for subdir in [os.path.join(taskdir, d) for d in os.listdir(taskdir)]:
            if (not os.path.isdir(subdir)): continue
            if (not 'crab_' in subdir): continue

            print subdir
            
            if (opt.RESUBMIT): cmd = 'crab resubmit -d '+str(subdir)
            elif (opt.KILL): cmd = 'crab kill -d '+str(subdir)
            elif (opt.STATUS): cmd = 'crab status -d '+str(subdir)
            elif (opt.PURGE): cmd = 'crab purge -d '+str(subdir)
            elif (opt.REPORT): cmd = 'crab report -d '+str(subdir)
            
            print cmd
            output = processCmd(cmd) 
            if (opt.STATUS):
                print output
                print ''
                print ''

        if (not opt.LOOP): break
        else: 
            print "waiting 30 minutes..." 
            time.sleep(60*30)

if __name__ == "__main__": 
    manage() 
