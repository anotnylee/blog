:restart
@echo off

set timeout=3
@echo "Try to Aim edit control, in %timeout% seconds"
ping -n %timeout% -w 1000 1.0.0.1 > NUL
aimedit "95599#�������������û�����¼#AfxWnd80su"
::aimedit "boc#�й�����#ATL:07765390"
::aimedit "icbc#�й�����������һ����������#ATL:Edit"
::aimedit "95559#��ͨ���и�������#ATL:Edit"
::aimedit "cmbchina#pbsz.ebank.cmbchina.com#ATL:07741200"

@echo "Try to input password, in %timeout% seconds"
::ping -n %timeout% -w 1000 1.0.0.1 > NUL
keyinput "abcAB123!@"

@echo "Input is Done"

goto restart
