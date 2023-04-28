#!/usr/bin/python
#-----------------------------------------------
# Latest update: 2014.09.14
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
    parser.add_option('-t', '--tag', dest='TAG', type='string',default='', help='tag to be appended to the results, default is an empty string')
    parser.add_option('-d', '--datasets', dest='DATASETS', type='string', default='datasets_Fall15_25ns_MiniAODv1.txt', help='txt file with datasets to run over')
    parser.add_option('-e', '--events', dest='EVENTS', type='string', default='events.txt', help='configuration template')

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

def submitPickEvents():

    # parse the arguments and options
    global opt, args
    parseOptions()

    # save working dir
    currentDir = os.getcwd()

    tag = opt.TAG
    outDir='resultsPickEvents_'+tag 

    if (not os.path.isdir(outDir)):
        cmd = 'mkdir '+outDir
        processCmd(cmd)
        cmd = 'mkdir '+outDir+'/cfg/'
        processCmd(cmd)

    # get the datasets
    print '[Gathering Dataset Information]'
    datasets = []
    cross_section = {}
    nfiles = {}
    nevents = {}
    datasetfiles = {}

    with open(opt.DATASETS, "r") as datasetfile:
        for line in datasetfile:

            if (line.startswith('#')): continue

            dataset = line.split()[0]
            dataset = dataset.rstrip()
            dataset = dataset.lstrip()

            datasets.append(dataset)
            cross_section[dataset] = float(line.split()[1])
            
            print dataset,'xs:',cross_section[dataset]


    # submit the jobs
    print '[Submitting jobs]'
    jobCount=0

    for dataset in datasets:
        
        #continue
        filename = dataset.split('/')[1]+'_'+dataset.split('/')[2]

        cfgfile = dataset.lstrip('/')
        cfgfile = cfgfile.replace('/','_')+'.py'

        filename = dataset.split('/')[1]+'_'+dataset.split('/')[2]
        if (len(filename)>99):
          newfilename = filename.split('-PU')[0]
          filename = newfilename

        crabcfgfile = 'crabConfigPickEvents_'+filename+'.py'             

        cmd = 'cp crabConfigPickEvents_TEMPLATE.py '+outDir+'/cfg/'+crabcfgfile
        output = processCmd(cmd)

        cmd  = "sed -i 's~OUTFILENAME~"+filename+"~g' "+outDir+'/cfg/'+crabcfgfile
        output = processCmd(cmd)

        cmd = "sed -i 's~JOBTAG~"+tag+"~g' "+outDir+'/cfg/'+crabcfgfile
        output = processCmd(cmd)

        cmd = "sed -i 's~DATASETNAME~"+dataset+"~g' "+outDir+'/cfg/'+crabcfgfile
        output = processCmd(cmd)

        cmd = 'crab submit -c '+outDir+'/cfg/'+crabcfgfile
        print cmd     

        output = processCmd(cmd) 
        while ('error' in output): 
            time.sleep(1.0); 
            output = processCmd(cmd) 
            if ('error' not in output):
                print 'Submitted after retry'
        print output

# run the submitAnalyzer() as main() 
if __name__ == "__main__": 
    submitPickEvents() 
