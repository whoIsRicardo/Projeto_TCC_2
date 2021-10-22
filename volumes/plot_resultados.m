clear all
close all
c1 = 1.526200;
c2 = 1.732994;
K=32;
K=32;
particulas = 64;
ws = 60E-19; 
q = 256;
iteracoes = 1800;
Nst = 1 : iteracoes;
SIR_max_dB=20;
SIR_max=10^(SIR_max_dB/10);
sigma_cc2=1e-2;
CIR_target=SIR_max*(sigma_cc2/q^2);
%CIR_target=SIR_max*(200e9/10e9)
SNR_target = CIR_target;

arquivo = fopen('C:/Users/Ricardo/Desktop/teste/p1_out.txt');
% A = fscanf(arquivo,'%f',[colunas linhas]);
Popt = fscanf(arquivo,'%f');
fclose(arquivo);
clear arquivo


arquivo = fopen('C:/Users/Ricardo/Desktop/Projeto_de_TCC-main/volumes/volume_1/SNR.bin');
% A = fscanf(arquivo,'%f',[colunas linhas]);
SNR = fscanf(arquivo,'%f');
fclose(arquivo);
clear arquivo

arquivo = fopen('C:/Users/Ricardo/Desktop/Projeto_de_TCC-main/volumes/volume_1/jPgbest.bin');
% A = fscanf(arquivo,'%f',[colunas linhas]);
jPgbest = fscanf(arquivo,'%f');
fclose(arquivo);
clear arquivo ans


arquivo = fopen('C:/Users/Ricardo/Desktop/Projeto_de_TCC-main/volumes/volume_1/SNIR.bin');
% A = fscanf(arquivo,'%f',[colunas linhas]);
sniraux = fscanf(arquivo,'%f',[K iteracoes]);
fclose(arquivo);
clear arquivo ans



arquivo = fopen('C:/Users/Ricardo/Desktop/Projeto_de_TCC-main/volumes/volume_1/Pgbest.bin');
% A = fscanf(arquivo,'%f',[colunas linhas]);
bestaux = fscanf(arquivo,'%f',[K iteracoes]);
fclose(arquivo);
clear arquivo ans

figure(1)
semilogy(Nst,bestaux(1,:)')
hold on
semilogy(Nst,bestaux')
semilogy(Nst,repmat(Popt,1,iteracoes),'k--')
Nstt=transpose(bestaux');
save power_pso Nstt -ASCII
Nstt=transpose(repmat(Popt,1,iteracoes));
save power_pso_op Nstt -ASCII
xlabel('IteraÃ§Ãµes')
ylabel('PotÃªncia transmitida (W)')
title(['Allocated Power, K = ',num2str(K,3),', Swarm Population, M = ',num2str(particulas,5),' particles  ', '\phi_1 = ',num2str(c1),'  \phi_2 = ',num2str(c2)])

figure(2)
plot(Nst,sum(repmat(Popt,1,iteracoes))./sum(bestaux),'LineWidth',2)
Nstt=transpose(sum(repmat(Popt,1,iteracoes))./sum(bestaux));
legend('Taxa de convergÃªncia pelo nÃºmero de iteraÃ§Ãµes')
xlabel('IteraÃ§Ãµes')
ylabel('Taxa de convergÃªncia')
save conver Nstt -ASCII


figure(3)
plot(10*log10((q^2/sigma_cc2).*sniraux'))
hold on
%plot(10*log10((q^2/sigma_cc2).*sniraux)-7)
plot(repmat(10*log10((sigma_cc2).*SNR_target),1,iteracoes),'k--','LineWidth',2.5)
ylabel('CIR')

