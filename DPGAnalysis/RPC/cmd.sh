#ls /eos/cms/store/express/Run2017E/ExpressPhysics/FEVT/Express-v1/000/304/291/00000/ > files.txt
ls /eos/cms/store/express/Run2017F/ExpressPhysics/FEVT/Express-v1/000/306/122/00000/ > files.txt
#cmsRun test/testRPCUnpackers_cfg.py inputFiles_load=files.txt filePrepend="/store/express/Run2017E/ExpressPhysics/FEVT/Express-v1/000/304/291/00000/"
cmsRun test/testRPCUnpackers_cfg.py inputFiles_load=files.txt filePrepend="/store/express/Run2017F/ExpressPhysics/FEVT/Express-v1/000/306/122/00000/"
edmDumpEventContent testRPCUnpackers.root > dumpUnpacker.txt
cmsRun test/testRPCUnpackersPlotter_cfg.py inputFiles=file:testRPCUnpackers.root
root l1 testRPCUnpackersPlotter.root
