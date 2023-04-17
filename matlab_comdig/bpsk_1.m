%% Parámetros del sistema
nBits = 10000;          % Número de bits transmitidos
Eb = 1;                 % Energía promedio por bit
SNR_dB = input('Ingrese el valor de SNR en dB: '); % SNR en dB
SNR = 10^(SNR_dB/10);    % SNR en escala lineal
N0 = Eb/SNR;            % Densidad espectral de potencia del ruido
BER = 0;                % Número de errores por bit

%% Generador de datos de Bernoulli
bits = randi([0 1],1,nBits);

%% Modulador BPSK
symb = 1 - 2*bits;

%% Canal AWGN
% Señal ruido (compleja)
sigma = sqrt(N0/2);
ruido_real = sigma*randn(1,nBits);
ruido_imag = sigma*randn(1,nBits);

% Señal recibida (s + ruido)
rx = symb + ruido_real + 1i*ruido_imag;

%% Demodulador BPSK
bits_rx = real(rx)<0;

%% Cálculo del BER
BER = sum(bits~=bits_rx)/nBits;

%% Visualización del diagrama de constelación
figure
plot(real(rx), imag(rx), '.', 'MarkerSize', 10)
title(['Diagrama de constelación con SNR = ' num2str(SNR_dB) ' dB'])
xlabel('Parte real')
ylabel('Parte imaginaria')
ylim([-4 4]) % Ajuste del eje Y

%% Salida de resultados
disp(['Número de errores obtenidos: ' num2str(sum(bits~=bits_rx))])
disp(['BER obtenido: ' num2str(BER)])
