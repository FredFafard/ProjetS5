################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/c/C6713Helper_UdeS.obj: ../source/c/C6713Helper_UdeS.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv7/tools/compiler/c6000_7.4.20/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/Users/Utilisateur/Documents/Genie electrique/S5/Projet S5/Workspace_10/Projet_S5_P1v1/Includes" --include_path="C:/ti/ccsv7/ccs_base/C6700/dsplib/include" --include_path="C:/ti/ccsv7/ccs_base/C6xCSL/include" --include_path="C:/ti/dsk6713/include" --define=CHIP_6713 --diag_wrap=off --display_error_number --diag_warning=225 --mem_model:data=far --mem_model:const=far --preproc_with_compile --preproc_dependency="source/c/C6713Helper_UdeS.d" --obj_directory="source/c" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/c/CorrX.obj: ../source/c/CorrX.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv7/tools/compiler/c6000_7.4.20/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/Users/Utilisateur/Documents/Genie electrique/S5/Projet S5/Workspace_10/Projet_S5_P1v1/Includes" --include_path="C:/ti/ccsv7/ccs_base/C6700/dsplib/include" --include_path="C:/ti/ccsv7/ccs_base/C6xCSL/include" --include_path="C:/ti/dsk6713/include" --define=CHIP_6713 --diag_wrap=off --display_error_number --diag_warning=225 --mem_model:data=far --mem_model:const=far --preproc_with_compile --preproc_dependency="source/c/CorrX.d" --obj_directory="source/c" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/c/SPI_driver.obj: ../source/c/SPI_driver.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv7/tools/compiler/c6000_7.4.20/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/Users/Utilisateur/Documents/Genie electrique/S5/Projet S5/Workspace_10/Projet_S5_P1v1/Includes" --include_path="C:/ti/ccsv7/ccs_base/C6700/dsplib/include" --include_path="C:/ti/ccsv7/ccs_base/C6xCSL/include" --include_path="C:/ti/dsk6713/include" --define=CHIP_6713 --diag_wrap=off --display_error_number --diag_warning=225 --mem_model:data=far --mem_model:const=far --preproc_with_compile --preproc_dependency="source/c/SPI_driver.d" --obj_directory="source/c" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/c/bitrev_index.obj: ../source/c/bitrev_index.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv7/tools/compiler/c6000_7.4.20/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/Users/Utilisateur/Documents/Genie electrique/S5/Projet S5/Workspace_10/Projet_S5_P1v1/Includes" --include_path="C:/ti/ccsv7/ccs_base/C6700/dsplib/include" --include_path="C:/ti/ccsv7/ccs_base/C6xCSL/include" --include_path="C:/ti/dsk6713/include" --define=CHIP_6713 --diag_wrap=off --display_error_number --diag_warning=225 --mem_model:data=far --mem_model:const=far --preproc_with_compile --preproc_dependency="source/c/bitrev_index.d" --obj_directory="source/c" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/c/main.obj: ../source/c/main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv7/tools/compiler/c6000_7.4.20/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/Users/Utilisateur/Documents/Genie electrique/S5/Projet S5/Workspace_10/Projet_S5_P1v1/Includes" --include_path="C:/ti/ccsv7/ccs_base/C6700/dsplib/include" --include_path="C:/ti/ccsv7/ccs_base/C6xCSL/include" --include_path="C:/ti/dsk6713/include" --define=CHIP_6713 --diag_wrap=off --display_error_number --diag_warning=225 --mem_model:data=far --mem_model:const=far --preproc_with_compile --preproc_dependency="source/c/main.d" --obj_directory="source/c" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/c/signalFFT.obj: ../source/c/signalFFT.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv7/tools/compiler/c6000_7.4.20/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/Users/Utilisateur/Documents/Genie electrique/S5/Projet S5/Workspace_10/Projet_S5_P1v1/Includes" --include_path="C:/ti/ccsv7/ccs_base/C6700/dsplib/include" --include_path="C:/ti/ccsv7/ccs_base/C6xCSL/include" --include_path="C:/ti/dsk6713/include" --define=CHIP_6713 --diag_wrap=off --display_error_number --diag_warning=225 --mem_model:data=far --mem_model:const=far --preproc_with_compile --preproc_dependency="source/c/signalFFT.d" --obj_directory="source/c" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


