# =====================================================
# TUGAS 13.3 - SOAL 2
# if (nilai >= 75) status = 1; else status = 0;
# Uji 1: nilai = 80, Uji 2: nilai = 60
# Nama  : Satrio Nurcahya
# NIM   : 1303180078
# =====================================================

.data
    pesanStatus : .asciiz "Nilai status = "

.text
.globl main

main:
    # =================== UJI 1 ===================
    li $t0, 80          # nilai = 80

    # Bandingkan nilai >= 75
    # slt $t1, $t0, 75 -> $t1 = 1 jika nilai < 75
    slt $t1, $t0, 75    # $t1 = 0 karena 80 < 75 salah

    beq $t1, $zero, status_1     # jika nilai < 75, lompat (tidak)
    # Blok else (nilai < 75)
    li $s0, 0
    j   tampil_1

status_1:
    li $s0, 1           # nilai >= 75

tampil_1:
    li $v0, 4
    la $a0, pesanStatus
    syscall

    li $v0, 1
    move $a0, $s0
    syscall

    # =================== UJI 2 ===================
    li $t0, 60          # nilai = 60

    slt $t1, $t0, 75    # $t1 = 1 karena 60 < 75

    beq $t1, $zero, status_2
    # Blok (nilai < 75)
    li $s0, 0
    j   tampil_2

status_2:
    li $s0, 1

tampil_2:
    li $v0, 4
    la $a0, pesanStatus
    syscall

    li $v0, 1
    move $a0, $s0
    syscall

    li $v0, 10
    syscall