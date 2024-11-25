# State Machine und gutes Code-Design

Schau dir zuvor den Code im ersten Repo, in der Datei pfui.txt an. Hier werden 
ausschliesslich Globals verwendet. Kann man machen, muss man aber nicht.

#### Die Vorteile der Statemachine

- **Klare Struktur**: Der Code ist modular aufgebaut, da jede Phase des Prozesses in einem eigenen Zustand (`state`) dargestellt wird.
- **Einfache Erweiterbarkeit**: Neue Zustände und Verhaltensweisen lassen sich leicht hinzufügen, indem weitere `case`-Blöcke in die `switch`-Anweisung integriert werden.
- **Wiederverwendbarkeit**: Die Statemachine ist unabhängig von der Hardware oder anderen Funktionen. Sie kann in ähnlichen Projekten wiederverwendet werden.
- **Verbesserte Wartbarkeit**: Logik und Zustände sind zentral organisiert, was die Fehlersuche und Änderungen erleichtert.
- **Lesbarkeit**: Klare Namensgebung und das Trennen von Zuständen und Aktionen machen den Code leicht verständlich.

#### Inhalt und Funktionsweise einer State Machine

**Hauptkomponenten**:
   - **Zustände**: Jeder Zustand repräsentiert eine bestimmte Phase oder ein bestimmtes Verhalten des Systems.
   - **Übergänge**: Übergänge bestimmen, wie und wann das System von einem Zustand in einen anderen wechselt.
   - **Aktionen**: Aktionen sind mit Zuständen oder Übergängen verknüpft und definieren, was bei einem Wechsel geschieht.

#### Erklärung des Codes

- **Zustände**: Die Statemachine hat vier Zustände: `OFF`, `ON`, `SINGLE_BLINK`, und `LONG_BLINK`.
- **Übergänge**:
  - Von `OFF` zu `ON` nach 2 Sekunden.
  - Von `ON` zu `SINGLE_BLINK` nach 2 Sekunden.
  - Von `SINGLE_BLINK` zu `LONG_BLINK` nach 10 kurzen Blinks.
  - Von `LONG_BLINK` zurück zu `OFF` nach 3 langen Blinks.
- **Aktionen**:
  - Jeder Zustand führt spezifische Aktionen aus, wie das Ein- oder Ausschalten einer LED mit definierten Zeitintervallen.
- **Verwendung von `switch`**:
  - Das `switch`-Statement erlaubt eine saubere und effiziente Steuerung des Verhaltens basierend auf dem aktuellen Zustand.

Kein zurücksetzten mehr von Globals und Variablen!
Dieses Beispiel ist eine gute Grundlage, um robuste und skalierbare Programme für eingebettete Systeme zu entwickeln. 

