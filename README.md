# 🔒 GNL Secure CI/CD

Un proyecto **Get Next Line (GNL)** de la escuela 42, mejorado con una pipeline de CI/CD enfocada en **DevSecOps** y testing automático.

## 📋 Descripción del Proyecto

El objetivo de este experimento es aprender el uso de GitHub Actions, y aplicar la teoría aprendida a un caso "real".

## 🎓 Aprendizaje: DevSecOps Pipeline

Este proyecto implementa conceptos clave de **DevSecOps**:

✅ **CI/CD Automation**: Deploy automático seguro  
✅ **SAST**: Análisis estático de seguridad  
✅ **DAST**: Testing dinámico (Valgrind)  
✅ **Container Security**: Escaneo de imágenes  
✅ **Supply Chain**: SBOM + firma digital  
✅ **Compliance**: Auditoría y trazabilidad

Este proceso de **testing, análisis de seguridad y scanning de vulnerabilidades** es necesario para garantizar código robusto y seguro.

## 🛠️ Estructura del Proyecto

```
gnl-secure-ci/
├── README.md                          # Este archivo
├── Dockerfile                         # Imagen Docker segura
├── Makefile                           # Build automation
├── .github/
│   └── workflows/
│       └── ci.yml                     # Pipeline de CI/CD
├── src/                               # Código del GNL
└── tests/
    ├── run_tests.sh                   # Script de tests
    ├── expected/                      # Outputs esperados
    └── inputs/                        # Inputs requeridos para el programa
```

---

## 🚀 Características Principales

### ✅ **Compilación Flexible**
- Compila con diferentes tamaños de buffer (`BUFFER_SIZE`)
- Garantiza robustez bajo diferentes restricciones de memoria
- Flags de seguridad: `-Wall -Wextra -Werror`

### 🧪 **Testing Automático**
- Suite de tests funcionales automatizados
- Valida correctitud ante múltiples inputs y edge cases
- Ejecución en matrix: buffer sizes [1, 42, 100]

### 🔍 **Análisis de Seguridad (SAST)**
- **Semgrep**: Detección de patrones inseguros y vulnerabilidades
- **Cppcheck**: Análisis estático profundo para C (memory issues, null pointers)

### 💾 **Memory Safety**
- **Valgrind**: Detección de memory leaks y buffer overflows
- Cada build debe pasar sin leaks antes de producción

### 🐳 **Containerización Segura**
- Imagen Docker Alpine 3.19 (minimal, 5MB)
- **Trivy**: Scanning de vulnerabilidades en imagen

### 📦 **Supply Chain Security**
- **SBOM** (Software Bill of Materials) generado con Syft
- Inventario de todas las dependencias para auditoría futura
- Trazabilidad completa en caso de CVE

### 🔐 **Integridad de Artefactos**
- Firma GPG digital del binario compilado
- Verificación de autoría: `gpg --verify app.asc app`

### 📊 **Auditoría y Cumplimiento**
- Artefactos almacenados 30 días
- Trazabilidad de builds para compliance normativo

---

## 🏗️ Arquitectura

```
┌─────────────────────────────────────────────────────┐
│                   Git Push / PR                     │
└────────────────┬────────────────────────────────────┘
                 │
         ┌───────▼────────┐
         │  GitHub Actions │  (Triggers on push/PR)
         └───────┬────────┘
                 │
    ┌────────────┼────────────┐
    ▼            ▼            ▼
┌────────┐  ┌────────┐  ┌────────┐
│Buffer  │  │Buffer  │  │Buffer  │  (Matriz de testing)
│Size: 1 │  │Size:42 │  │Size:100│
└────┬───┘  └───┬────┘  └───┬────┘
     │          │           │
     └──────────┼───────────┘
                │
    📝 COMPILACIÓN & TEST
    🔍 ANÁLISIS ESTÁTICO  
    💾 MEMORY CHECKING
    🐳 CONTAINER SCANNING
    📦 SUPPLY CHAIN (SBOM)
    🔐 SIGNING & VERIFICATION
    📦 ARTIFACT UPLOAD
                │
         ┌──────▼───────┐
         │   SUCCESS    │
         │  ✓ app       │
         │  ✓ app.asc   │
         │  ✓ sbom.json │
         └──────────────┘
```
---

## 🔬 Pipeline de Seguridad Detallado

### 1️⃣ **Compilación (CI)**
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 src/*.c -o app
```
✓ Compila con flags estrictos de advertencia  
✓ Cero tolerancia a warnings (`-Werror`)

---

### 2️⃣ **Tests Funcionales**
```bash
./tests/run_tests.sh
```
✓ Valida comportamiento correcto  
✓ Tests contra múltiples inputs  
✓ Verifica edge cases

---

### 3️⃣ **Memory Safety (Valgrind)**
```bash
valgrind --leak-check=full ./app tests/inputs/test1.txt
```
✓ Detección de memory leaks  
✓ Buffer overflows  
✓ Use-after-free bugs  
⚠️ Crítico en C

---

### 4️⃣ **Análisis Estático - Semgrep**
Busca vulnerabilidades comunes:
- Hardcoded credentials
- Unsafe functions (strcpy, sprintf)
- Injection flaws
- Logic errors

Usa reglas mantenidas por profesionales de seguridad.

---

### 5️⃣ **Análisis Estático - Cppcheck**
Análisis profundo específico para C:
- Errores lógicos
- Memory issues
- Null pointer dereferences
- Dead code
- Rendimiento

---

### 6️⃣ **Container Scanning (Trivy)**
```bash
docker build -t gnl-secure-ci .
trivy image gnl-secure-ci
```
✓ Escanea imagen en busca de CVEs  
✓ Verifica base Alpine 3.19  
✓ Previene desplegar vulnerabilidades

---

### 7️⃣ **Supply Chain Security (SBOM)**
```bash
syft app -o json > sbom.json
```
✓ Inventario de todas las dependencias  
✓ Versiones exactas  
✓ Mostra licencias  
✓ Auditoría futura si CVE emerge

Ejemplo de salida:
```json
{
  "artifacts": [
    {
      "name": "libc",
      "version": "1.2.3",
      "type": "library"
    }
  ]
}
```

---

### 8️⃣ **Artifact Signing (GPG)**
```bash
gpg --batch --generate-key < key-config
gpg --armor --detach-sign ./app
gpg --verify app.asc app
```

**¿Por qué?**
- Garantiza que el binario no fue modificado
- Verifica que viene del CI (auténtico)
- Cadena de confianza: repo → CI → firma → distribución

**Cómo verificar localmente:**
```bash
# Importar clave pública
gpg --import public.key

# Verificar
gpg --verify app.asc app
```

---

### 9️⃣ **Artefactos para Auditoría**
Se guardan 30 días en GitHub Actions:
- `app`: binario compilado
- `app.asc`: firma GPG
- `sbom.json`: inventario de dependencias

Descárgalos desde: `Actions → [Build] → Artifacts`
