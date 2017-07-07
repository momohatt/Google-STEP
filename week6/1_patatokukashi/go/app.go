package app

import (
	"html/template"
	"net/http"
)

func init() {
	http.HandleFunc("/", handlePata)
}

func handlePata(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "text/html; charset=utf-8")
	a := r.FormValue("a")
	b := r.FormValue("b")
	result := combine(a, b)
	tmpl := template.Must(template.ParseFiles("./index.html"))
	tmpl.Execute(w, result)
}

func combine(a, b string) string {
	result := ""
	longer := ""
	shorter := ""
	if len([]rune(a)) < len([]rune(b)) {
		longer = b
		shorter = a
	} else {
		longer = a
		shorter = b
	}

    for i := 0; i < len([]rune(shorter)); i++ {
		result += string([]rune(longer)[i])
		result += string([]rune(shorter)[i])
	}
    for i := len([]rune(shorter)); i < len([]rune(longer)); i++ {
		result += string([]rune(longer)[i])
	}
	return result
}
