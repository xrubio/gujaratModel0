#!/usr/bin/python
import fileinput, sys, os, random

mapSizes = ['800']

numExecutions = 1
numHGs = ['50']
controllers = ['Random', 'DecisionTree', 'MDP']

xmlTemplate = 'templates/config_template_mn_gpfs.xml'
runTemplate = 'templates/run_template.cmd'

mapSizeKey = 'MAPSIZE'
numHGKey = 'NUMHG'
controllerKey = 'CTYPE'

indexKey = 'INDEX'
initialDirKey = 'INITIALDIR'
numExecutionKey = 'NUMEXEC'

climateKey = 'CLIMATESEED'


def replaceKey( fileName, key, value ):
	for line in fileinput.FileInput(fileName,inplace=1):
		if key in line:
			line = line.replace(key, value)
		sys.stdout.write(line)
	fileinput.close()

os.system('rm -rf results_*')

index = 0
print 'creating test workbench'

random.seed()

for numExecution in range(0,numExecutions):
	# each n.execution  has the same seed in all parameter space
	randomValue = str(random.randint(0,10000000))
	for mapSize in mapSizes:
		for numHG in numHGs:
			for controller in controllers:
				print 'creating gujarat instance: ' + str(index) + ' for map: ' + mapSize + ' numHG: ' + numHG + ' with controller: ' + controller + ' and execution: ' + str(numExecution)
				dirName = 'results_size'+mapSize+'_numHG'+numHG+'_controller_'+controller+'_ex'+str(numExecution)
				os.system('mkdir '+dirName)
				configName = dirName + '/config.xml'			
				os.system('cp '+xmlTemplate+' '+configName)
				replaceKey(configName, mapSizeKey, mapSize)
				replaceKey(configName, numHGKey, numHG)
				replaceKey(configName, controllerKey, controller)
				replaceKey(configName, climateKey, randomValue)
				replaceKey(configName, numExecutionKey, str(numExecution))

				runName = dirName+'/run.cmd'
				os.system('cp '+runTemplate+' '+runName)
				replaceKey(runName, indexKey, str(index))
				replaceKey(runName, initialDirKey, dirName)
				index += 1

print 'workbench done, submitting tasks'
index = 0
for mapSize in mapSizes:
	for numHG in numHGs:
		for controller in controllers:	
			for numExecution in range(0,numExecutions):
				print 'submitting gujarat instance: ' + str(index) + ' for map: ' + mapSize + ' numHG: ' + numHG + ' with controller: ' + controller + ' and execution: ' + str(numExecution)
				dirName = 'results_size'+mapSize+'_numHG'+numHG+'_controller_'+controller+'_ex'+str(numExecution)
				os.system('mnsubmit '+dirName+'/run.cmd')
				index += 1

