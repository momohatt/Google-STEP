package app

import (
    "net/http"
    "html/template"
    "google.golang.org/appengine"
    "google.golang.org/appengine/urlfetch"
)

func init() {
    http.HandleFunc("/", handleStationName)
}

func handleStationName(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Content-Type", "text/html; charset=utf-8")
    ctx := appengine.NewContext(r)
    client := urlfetch.Client(ctx)
    resp, err := client.Get("http://lotr.fantasy-transit.appspot.com/net?format=json")
    if err != nil {
        http.Error(w, err.Error(), http.StatusInternalServerError)
        return
    }
    
}

func bfs() {
}
